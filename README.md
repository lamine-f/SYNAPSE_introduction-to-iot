# Projet Synapse - Contrôle MQTT d'LED

Ce projet permet de contrôler l'état d'une LED à travers une interface web et Node-RED, en utilisant le protocole MQTT pour la communication.

## Table des matières
- [Aperçu](#aperçu)
- [Prérequis](#prérequis)
- [Installation](#installation)
- [Structure du projet](#structure-du-projet)
- [Configuration](#configuration)
- [Utilisation](#utilisation)
- [Architecture](#architecture)
- [Dépannage](#dépannage)

## Aperçu

Ce projet illustre l'utilisation du protocole MQTT pour créer une communication bidirectionnelle entre:
- Une interface web (client MQTT)
- Un serveur Node-RED (broker MQTT)
- Un potentiel appareil physique avec LED (non inclus dans ce dépôt)

L'interface permet d'allumer/éteindre une LED virtuellement et affiche différents médias (images et vidéos) en fonction de son état.

## Captures d'écran

[Insérer captures d'écran de l'interface web ici]

## Prérequis

- Node.js et npm (https://nodejs.org/)
- Node-RED (https://nodered.org/)
- Un navigateur web moderne
- Connexion Internet (pour le broker MQTT public)

## Installation

1. **Cloner ce dépôt:**
   ```bash
   git clone [URL-du-dépôt]
   cd presentation-synapse
   ```

2. **Installer Node.js et npm** si ce n'est pas déjà fait:
   - Visiter [nodejs.org](https://nodejs.org/) et télécharger la version LTS
   - Suivre les instructions d'installation pour votre système d'exploitation

3. **Installer Node-RED:**
   ```bash
   npm install -g --unsafe-perm node-red
   ```

4. **Démarrer Node-RED:**
   ```bash
   node-red
   ```
   Node-RED sera accessible à l'adresse http://localhost:1880/

5. **Importer le flux dans Node-RED:**
   - Ouvrir Node-RED dans votre navigateur
   - Cliquer sur le menu hamburger (en haut à droite)
   - Sélectionner "Import"
   - Copier le contenu du fichier `flow.json` ou importer directement le fichier
   - Cliquer sur "Import"

6. **Configurer la bibliothèque Paho MQTT:**
   - La bibliothèque `paho-mqtt-min.js` est déjà incluse dans le projet (`MQTT_WEB_CLIENT/js/libs/paho.javascript-1.0.3/paho-mqtt-min.js`)

7. **Ouvrir l'interface web:**
   - Ouvrir le fichier `MQTT_WEB_CLIENT/index.html` dans un navigateur web

## Structure du projet

```
presentation-synapse/
├── flow.json                      # Configuration Node-RED
├── README.md                      # Ce fichier
└── MQTT_WEB_CLIENT/               # Client web MQTT
    ├── index.html                 # Page principale
    ├── js/
    │   ├── mqtt/
    │   │   └── mqtt.js            # Configuration et gestion MQTT
    │   ├── ui/
    │   │   └── ui.js              # Logique d'interface utilisateur
    │   └── libs/
    │       └── paho.javascript-1.0.3/
    │           └── paho-mqtt-min.js  # Bibliothèque MQTT
    ├── styles/
    │   ├── global.css             # Styles globaux
    │   ├── media-content.css      # Styles pour les médias
    │   └── switch-button.css      # Styles pour le bouton interrupteur
    └── medias/                    # Dossier contenant les médias
```

## Configuration

### Configuration MQTT

La configuration MQTT se trouve dans le fichier `MQTT_WEB_CLIENT/js/mqtt/mqtt.js`:

```javascript
const Configuration = {
    brokerUrl : 'broker.emqx.io',  // URL du broker MQTT public
    port : 8083,                    // Port WebSocket
    topic : '@lord-nighteyes/led/1/management',  // Topic MQTT
    clientId : 'webClientId_' + Math.random().toString(16).substring(2, 8),
}
```

Vous pouvez modifier ces paramètres pour utiliser un broker MQTT différent si nécessaire.

## Utilisation

1. **Démarrer Node-RED** (s'il n'est pas déjà en cours d'exécution):
   ```bash
   node-red
   ```

2. **Ouvrir l'interface web** en ouvrant le fichier `MQTT_WEB_CLIENT/index.html` dans un navigateur.

3. **Contrôler la LED:**
   - Cliquer sur l'interrupteur pour allumer/éteindre la LED
   - L'état sera synchronisé entre l'interface web et Node-RED
   - Vous pouvez également appuyer sur la barre d'espace pour basculer l'état

4. **Accéder au tableau de bord Node-RED:**
   - Ouvrir http://localhost:1880/ui dans votre navigateur
   - Vous verrez l'état de la LED et pourrez également la contrôler depuis Node-RED

## Architecture

Le projet utilise une architecture basée sur MQTT:

1. **Client Web MQTT:**
   - Utilise la bibliothèque Paho MQTT pour se connecter au broker
   - Publie des messages sur le topic MQTT pour contrôler la LED
   - S'abonne au topic pour recevoir les mises à jour d'état

2. **Node-RED:**
   - S'abonne au même topic MQTT
   - Traite les messages et met à jour l'interface utilisateur Node-RED
   - Peut également envoyer des commandes à la LED

3. **Broker MQTT:**
   - Ce projet utilise le broker public EMQX (broker.emqx.io)
   - Gère la communication entre les clients

## Dépannage

### Problèmes de connexion MQTT

- Vérifier que vous êtes connecté à Internet (pour accéder au broker public)
- Vérifier les paramètres du broker dans `mqtt.js` et dans la configuration Node-RED
- Essayer d'utiliser un broker MQTT local pour les tests

### Problèmes avec Node-RED

- Vérifier que Node-RED est en cours d'exécution
- Vérifier les journaux Node-RED pour les erreurs
- S'assurer que le flux a été correctement importé

### Problèmes d'affichage des médias

- Vérifier que les chemins des fichiers médias sont corrects
- S'assurer que les formats de médias sont pris en charge par votre navigateur

