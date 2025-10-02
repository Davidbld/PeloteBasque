#!/bin/bash

# Couleurs pour les messages
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fonction pour afficher les messages d'erreur
error() {
    echo -e "${RED}Erreur: $1${NC}"
    exit 1
}

# Fonction pour afficher les messages de succès
success() {
    echo -e "${GREEN}$1${NC}"
}

# Fonction pour afficher les messages d'information
info() {
    echo -e "${YELLOW}$1${NC}"
}

# Vérifier si cmake est installé
if ! command -v cmake &> /dev/null; then
    error "CMake n'est pas installé. Veuillez installer CMake pour compiler le projet."
fi

# Vérifier si SFML est installé
if ! pkg-config --exists sfml-all; then
    error "SFML n'est pas installé. Veuillez installer SFML pour compiler le projet."
fi

# Créer le dossier build s'il n'existe pas
if [ ! -d "build" ]; then
    info "Création du dossier build..."
    mkdir build
fi

# Aller dans le dossier build
cd build || error "Impossible d'accéder au dossier build"

# Configurer le projet avec CMake
info "Configuration du projet avec CMake..."
cmake .. || error "Erreur lors de la configuration CMake"

# Compiler le projet
info "Compilation du projet..."
make -j$(nproc) || error "Erreur lors de la compilation"

success "Compilation terminée avec succès!"

# Exécuter le jeu
info "Lancement du jeu..."
./PeloteBasque