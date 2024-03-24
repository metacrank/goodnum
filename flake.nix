{
  description = "A goodnum library devshell environment";

  inputs.flake-utils.url = "github:numtide/flake-utils";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.11";

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let pkgs = nixpkgs.legacyPackages.${system}; in
        {
          devShells.default = import ./shell.nix { inherit pkgs; };
          stdenv.mkDerivation =
            {
              name = "main";
              src = self;
              buildPhase = '''';
              installPhase = ''sudo make install'';
            };
        }
      );
}
