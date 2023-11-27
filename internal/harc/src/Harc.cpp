#include <harc/Harc.hpp>

#include <harc/Translation_unit.hpp>
#include "harc/cli/CLI.hpp"
#include <harc/common/OS_utils.hpp>
#include <harc/Logging.hpp>
#include <harc/Error_reporting.hpp>

#include <harc/lexer/Lexer.hpp>
//#include <harc/Harc_cuda.hpp>

#include <harc/parser/Parser.hpp>
#include <harc/parser/Printer.hpp>

#include <harc/Errors.hpp>

#include <thread>
#include <mutex>
#include <chrono>

#include <vector>

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#if HARC_CUDA
    #include <cuda_runtime.h>
#endif

namespace harc {

    ///
    /// Enum used to indicate which
    ///
    enum class Compilation_step : std::uint8_t {
        NULL_STEP,
        FRONTEND,
        BACKEND
    };

    struct Task {
        Compilation_step step = Compilation_step::NULL_STEP;
        Translation_unit unit;
    };

    ///
    /// Perform compiler frontend work on the specified translation unit.
    ///
    /// \param unit Translation unit to perform frontend work for
    void run_frontend(Translation_unit& unit);

    ///
    /// Perform compiler backend work on teh specified translation unit.
    ///
    /// \param unit Translation unit to perform backend work for
    void run_backend(Translation_unit& unit);

    //=====================================================
    // Shared Worker State
    //=====================================================

    ///
    /// Queue containing units that need to be processed
    ///
    std::vector<Task> work_queue;

    ///
    /// Mutex used to protect translation_unit_queue variable
    ///
    std::mutex translation_unit_queue_mutex;

    ///
    /// Used to indicate if worker threads should terminate once there is no
    /// more work available for them to do.
    ///
    /// Set to false, when Harc is run as a client since Harc should then wait
    /// for the host to send more work in the future.
    ///
    std::atomic_bool terminate_once_idle = false;

    //=====================================================
    // CPU Worker State
    //=====================================================

    ///
    /// A list of all the threads which are used for CPU compilation
    ///
    std::vector<std::thread> cpu_worker_threads;

    //=====================================================
    // GPU Worker State
    //=====================================================

    std::vector<std::thread> cuda_worker_threads;

    //=====================================================
    // Server state
    //=====================================================

    //=====================================================
    // Client Worker State
    //=====================================================

    //=====================================================
    // Worker threads
    //=====================================================

    ///
    /// Function which is run for CPU threads used in compilation process
    ///
    void cpu_worker() {
        while (true) {
            // Retrieve task from queue
            Task task{};
            {
                std::lock_guard lk{translation_unit_queue_mutex};

                if (!work_queue.empty()) {
                    task = work_queue.back();
                    work_queue.pop_back();
                }
            }

            //
            if (Compilation_step::NULL_STEP == task.step) {
                if (terminate_once_idle) {
                    break;
                } else {
                    //TODO: Replace with wait for wake-up event
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(100ms);
                    continue;
                }
            }

            // Compile on CPU
            auto& unit = task.unit;
            if (Compilation_step::FRONTEND == task.step) {
                using clk = std::chrono::steady_clock;

                //TODO: Time work

                lex::lex(unit);
                HARC_LOG_INFO("TOKENIZATION:\n{}\n", tokenization_to_string(unit));

                parser::parse(unit);
                HARC_LOG_INFO("PARSE TREE:\n{}\n", parse_tree_to_string(unit));
            }
        }
    }

    #if HARC_CUDA
    ///
    /// Function which is run to assign work to CUDA streams
    ///
    void cuda_worker(int device_index, cudaStream_t stream) {
        cudaSetDevice(device_index);

        while (true) {
            Task task{};
            {
                std::lock_guard lk{translation_unit_queue_mutex};

                if (!work_queue.empty()) {
                    task = work_queue.back();
                    work_queue.pop_back();
                }
            }

            if (Compilation_step::NULL_STEP == task.step) {
                if (terminate_once_idle) {
                    break;
                } else {
                    //TODO: Replace with wait for wake-up event
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(100ms);
                    continue;
                }
            }

            if (Compilation_step::FRONTEND == task.step) {
                //TODO: Invoke Tokenization kernels
            }
        }
    }
    #endif

    //=====================================================
    // Helper functions
    //=====================================================

    void create_cpu_worker_threads() {
        auto thread_count = std::thread::hardware_concurrency();

        for (std::size_t i = 0; i < thread_count; ++i) {
            cpu_worker_threads.emplace_back(cpu_worker);
        }
    }

    #if HARC_CUDA
    void create_cuda_worker_threads() {
        int device_count;
        cudaGetDeviceCount(&device_count);

        // This is currently an arbitrary number in need of refinement
        constexpr int streams_per_device = 8;

        // Create CUDA streams
        std::vector<std::array<cudaStream_t, streams_per_device>> device_streams;
        device_streams.resize(device_count);

        for (int i = 0; i < device_count; ++i) {
            for (int j = 0; j < streams_per_device; ++j) {
                cudaStreamCreate(device_streams[i].data() + j);
            }
        }

        // Launch threads
        cuda_worker_threads.reserve(device_count * streams_per_device);

        for (int i = 0; i < device_count; ++i) {
            for (int j = 0; j < streams_per_device; ++j) {
                cuda_worker_threads.emplace_back(
                    cuda_worker,
                    i,
                    device_streams[i][j]
                );
            }
        }
    }
    #endif

    void create_compilation_tasks() {
        for (auto& source_path : cli::arguments.source_paths) {
            work_queue.emplace_back();
            auto& task = work_queue.back();
            task.step = Compilation_step::FRONTEND;
            task.unit.source_path = source_path;

            #if HARC_POSIX
            Text_file_mapping mapping = map_text_file(source_path);
            if (mapping.error_code != Error_code::NO_ERROR) {
                Message_buffer::append(mapping.error_code);
                continue;
            }

            task.unit.source = mapping.text;
            unmap_file(mapping);

            #elif
            std::ifstream fin{source_path.data()};
            t.seekg(0, std::ios::end);
            std::size_t size = t.tellg();

            std::string buffer(size, ' ');
            t.seekg(0);
            t.read(&buffer[0], size);

            back.unit.source = std::move(buffer);

            #endif
        }

        //if (!Message_buffer::is_empty()) {
        //    return Error_code::GENERAL_INTERNAL_ERRORR;
        //}
    }

    //=====================================================
    // Core Harc functions
    //=====================================================

    void run_client() {
        terminate_once_idle = false;

        create_cpu_worker_threads();
        #if HARC_CUDA
        create_cuda_worker_threads();
        #endif

        // Wait for threads to complete their work
        for (auto& th : cpu_worker_threads) {
            th.join();
        }

        #if HARC_CUDA
        for (auto& th : cuda_worker_threads) {
            th.join();
        }
        #endif
    }

    void run_pure_server() {
        if (cli::arguments.source_paths.empty()) {
            Message_buffer::append(Error_code::NO_SOURCE_FILES_SPECIFIED);
            return;
        }

        terminate_once_idle = true;

        create_compilation_tasks();
    }

    void run_server() {
        if (cli::arguments.source_paths.empty()) {
            Message_buffer::append(Error_code::NO_SOURCE_FILES_SPECIFIED);
            return;
        }

        terminate_once_idle = true;

        create_compilation_tasks();

        create_cpu_worker_threads();
        #if HARC_CUDA
        create_cuda_worker_threads();
        #endif

        // Wait for threads to complete their work
        for (auto& th : cpu_worker_threads) {
            th.join();
        }

        #if HARC_CUDA
        for (auto& th : cuda_worker_threads) {
            th.join();
        }
        #endif
    }

    void run_locally() {
        if (cli::arguments.source_paths.empty()) {
            Message_buffer::append(Error_code::NO_SOURCE_FILES_SPECIFIED);
            return;
        }

        terminate_once_idle = true;

        create_compilation_tasks();
        create_cpu_worker_threads();

        #if HARC_CUDA
        create_cuda_worker_threads();
        #endif

        // Wait for threads to complete their work
        for (auto& th : cpu_worker_threads) {
            th.join();
        }

        #if HARC_CUDA
        for (auto& th : cuda_worker_threads) {
            th.join();
        }
        #endif
    }

}
