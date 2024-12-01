{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell
{
  nativeBuildInputs = with pkgs; [
    gcc
    binutils
    gnumake
    autoconf
    automake
    libtool
    gdb
  ];
}
