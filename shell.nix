{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = with pkgs.buildPackages;
    let
        ca65-symbls-to-nl = pkgs.stdenv.mkDerivation rec {
            name = "ca65-symbls-to-nl";
            version = "1.0";

            src = ./.;

            DESTDIR = "$(out)";
        };
    in [
        ca65-symbls-to-nl
    ];
}