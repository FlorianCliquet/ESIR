# Couche Application - Detailed Recap

## Table of Contents
1. [Introduction](#1-introduction)
2. [Architecture des Applications](#2-architecture-des-applications)
   - [Modèle Client/Serveur](#a-modèle-clientserveur)
   - [Modèle Pair-à-pair (P2P)](#b-modèle-pair-à-pair)
3. [Les Sockets](#3-les-sockets)
4. [Services Applicatifs](#4-services-applicatifs)
5. [Applications](#5-applications)
   - [Telnet](#a-telnet)
   - [SSH](#b-ssh)
   - [HTTP](#c-http)
   - [FTP](#d-ftp)
   - [Messagerie (SMTP, POP3, IMAP)](#e-messagerie-smtp-pop3-imap)
   - [DNS](#f-dns)
6. [Peer-to-Peer (P2P)](#6-peer-to-peer-p2p)
7. [Questions](#7-questions)

---

## 1. Introduction
- **Couche Application** : Fournit l'accès aux services réseau et définit la communication entre processus utilisateurs. Elle est à la fois la source et la destination des données échangées.

---

## 2. Architecture des Applications

### a) Modèle Client/Serveur
- **Client** : Communique avec un serveur, souvent avec une IP dynamique. Peut se connecter de manière intermittente.
- **Serveur** : En écoute sur un hôte avec une IP fixe, gère les demandes des clients. Utilise souvent des clusters de serveurs pour gérer la charge.

**Schema: Modèle Client/Serveur**
```
  [Client 1] --> |           |
  [Client 2] --> | Serveur   | --> Base de données
  [Client 3] --> |           |
```

### b) Modèle Pair-à-pair (P2P)
- **P2P** : Pas de serveur central, chaque terminal (peer) communique directement avec d’autres. Ce modèle est plus scalable (l’ajout de peers augmente la capacité), mais implique une gestion plus complexe des IP dynamiques.

**Schema: Modèle P2P**
```
[Peer 1] <---> [Peer 2] <---> [Peer 3]
      |                |               |
    [Peer 4]         [Peer 5]         [Peer 6]
```

---

## 3. Les Sockets
- **Sockets** : Interface entre une application et la couche transport. Ils permettent l'envoi et la réception de données via des protocoles comme TCP et UDP.
- Les sockets permettent de choisir des paramètres comme le protocole de transport (TCP ou UDP).

**Schema: Communication via Sockets**
```
  Processus (A) --- Socket --- Transport (TCP/UDP) --- Socket --- Processus (B)
```

---

## 4. Services Applicatifs
- **Choix du service de transport** :
  - **Fiabilité** : Certaines applications (ex: FTP) nécessitent une transmission fiable sans perte de données.
  - **Débit** : Certaines applications multimédia nécessitent une bande passante minimale pour fonctionner correctement.
  - **Délai** : Des applications comme la VoIP ou les jeux interactifs exigent un faible délai pour garantir une bonne expérience utilisateur.

---

## 5. Applications

### a) Telnet
- **Fonction** : Protocole pour le contrôle à distance des machines.
- **Port** : 23
- **Caractéristiques** : Utilise TCP, envoie des commandes ASCII et contrôle à distance des terminaux via une connexion TCP unique.

**Schema: Telnet**
```
  [Client] ---(TCP, Port 23)--- [Serveur Telnet]
```

### b) SSH (Secure Shell)
- **Fonction** : Alternative sécurisée à Telnet. SSH chiffre les communications pour une meilleure sécurité.
- **Port** : 22
- **Caractéristiques** : Utilise des techniques de chiffrement (ex : AES), permettant une communication sécurisée entre client et serveur.

**Schema: SSH**
```
  [Client] ---(Chiffré, Port 22)--- [Serveur SSH]
```

### c) HTTP (Hypertext Transfer Protocol)
- **Fonction** : Protocole client-serveur pour le transfert de pages web.
- **Port** : 80
- **Version** : HTTP/1.1 permet des connexions persistantes par défaut.
- **Sans état** : Le serveur HTTP ne garde pas d'informations sur les requêtes précédentes.
  
**Schema: HTTP Communication**
```
  [Navigateur] -- Requête HTTP --> [Serveur Web]
  [Navigateur] <-- Réponse HTTP -- [Serveur Web]
```

**Modèle de Connexion HTTP (sans état)**

1. Client initie une connexion TCP (port 80)
2. Envoie une requête HTTP
3. Serveur envoie la réponse HTTP
4. La connexion TCP est fermée

### d) FTP (File Transfer Protocol)
- **Fonction** : Protocole client-serveur pour le transfert de fichiers.
- **Ports** : 21 (contrôle), 20 (données).
- **Caractéristiques** : FTP utilise deux connexions TCP — une pour le contrôle et une pour les données. Supporte les commandes pour gérer les fichiers à distance (USER, RETR, STOR).

**Schema: FTP**
```
  [Client FTP] --(TCP Port 21)-- [Serveur FTP] --- Système de fichiers distant
                  |                             
                  '--(TCP Port 20)-- Connexion de données
```

### e) Messagerie (SMTP, POP3, IMAP)

- **SMTP** : Protocole pour l'envoi d'e-mails.
  - **Port** : 25
  - Utilisé pour le transfert de mails entre serveurs de messagerie.
  
- **POP3** : Téléchargement des mails depuis le serveur.
  - **Mode** : Téléchargement puis suppression ou non-suppression.

- **IMAP** : Gestion des mails directement sur le serveur.
  - **Caractéristiques** : Permet de gérer les dossiers de mails, maintient l'état entre sessions.

**Schema: Protocole SMTP**
```
  [Agent Utilisateur] --> [Serveur SMTP] --> [Serveur de messagerie destinataire]
```

### f) DNS (Domain Name System)
- **Fonction** : Conversion des noms de domaine en adresses IP via une base de données distribuée et hiérarchique.
- **Processus** : Les requêtes DNS sont soit itératives soit récursives.
  
**Schema: DNS Résolution**
```
  [Client] --> [Serveur DNS local] --> [Serveur DNS racine] --> [Serveur DNS de domaine] --> [Adresse IP]
```

---

## 6. Peer-to-Peer (P2P)

### a) BitTorrent
- **Fonction** : Protocole de partage de fichiers en P2P. Les fichiers sont divisés en morceaux (chunks) partagés entre plusieurs peers.
- **Seeders** : Peers qui possèdent le fichier complet et le partagent.
- **Leechers** : Peers qui téléchargent des morceaux de fichiers.

**Schema: Modèle P2P avec BitTorrent**
```
  [Seeder] --> [Leecher 1] --> [Leecher 2]
              |                  |
            [Leecher 3] <--> [Leecher 4]
```

---

## 7. Questions
1. Quelle est la différence principale entre le modèle Client/Serveur et le modèle P2P?
2. Quelle est la fonction d'un socket dans la communication entre processus?
3. Pourquoi HTTP est-il dit "sans état" et quelles sont les implications?
4. Quels sont les rôles des ports 21 et 20 dans le protocole FTP?
5. Comment DNS résout-il les noms de domaine en adresses IP?
6. Quelle est la différence entre SMTP, POP3 et IMAP en termes de messagerie?
7. Dans le contexte P2P, quelle est la différence entre un seeder et un leecher?

