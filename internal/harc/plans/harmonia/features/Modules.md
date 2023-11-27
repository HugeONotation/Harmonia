# Modules
* Every source file and its contents belong to a single module file
* this module is declared as the first thing in a source file as `module [module_name];`
* the recommended naming convention is for modules to follow `Snake_case`
* the standard library is contained within the `std` module
* modules may be nested by up to 16 levels
* nested modules as expressed as in the example`Module0.Module1.Module2`
* modules may be import in whole `import Module0` or in part `import Module0.Member`
* import statements must follow the module declaration and before any other file contents
* 