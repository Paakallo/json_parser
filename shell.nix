{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.gdb
    pkgs.gnumake
    pkgs.cmake
  ];
}
