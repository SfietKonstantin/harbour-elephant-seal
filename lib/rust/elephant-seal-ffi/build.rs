use std::path::Path;
use std::{env, fs};

fn main() {
    println!("cargo:rerun-if-changed=src/lib.rs");

    let source = Path::new(&env::var("OUT_DIR").unwrap()).join("cxxbridge");
    cxx_qt_lib_headers::write_headers(source.join("include").join("cxx-qt-lib"));

    cxx_build::bridge("src/lib.rs")
        .flag_if_supported("-std=c++17")
        .include("..")
        .include("../../lib")
        .compile("elephant-seal-rust");

    if let Ok(cmake_current_binary_dir) = env::var("CMAKE_CURRENT_BINARY_DIR") {
        let target = Path::new(&cmake_current_binary_dir).join("cxxbridge");
        if target.exists() {
            fs::remove_dir_all(&target).unwrap();
        }
        copy_dir::copy_dir(source, &target).unwrap();
    }
}
