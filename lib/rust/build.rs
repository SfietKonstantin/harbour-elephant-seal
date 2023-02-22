use std::path::Path;
use std::{env, fs};

fn main() {
    println!("cargo:rerun-if-changed=src/ffi.rs");

    cxx_build::bridge("src/ffi.rs")
        .flag_if_supported("-std=c++17")
        .include(".")
        .compile("elephant-seal-rust");

    if let Ok(cmake_current_binary_dir) = env::var("CMAKE_CURRENT_BINARY_DIR") {
        let source = Path::new(&env::var("OUT_DIR").unwrap()).join("cxxbridge");
        let target = Path::new(&cmake_current_binary_dir).join("cxxbridge");
        if target.exists() {
            fs::remove_dir_all(&target).unwrap();
        }
        copy_dir::copy_dir(source, &target).unwrap();

        cxx_qt_lib_headers::write_headers(target.join("include").join("cxx-qt-lib"));
    }
}
