# Couche Transport - Récapitulatif Détailé

## Sommaire
1. [Introduction](#1-introduction)
2. [Principes généraux de la couche transport](#2-principes-généraux-de-la-couche-transport)
3. [UDP (User Datagram Protocol)](#3-udp-user-datagram-protocol)
   - [Introduction à UDP](#a-introduction-à-udp)
   - [Format des messages UDP](#b-format-des-messages-udp)
   - [Résumé UDP](#c-résumé-udp)
4. [TCP (Transmission Control Protocol)](#4-tcp-transmission-control-protocol)
   - [Introduction à TCP](#a-introduction-à-tcp)
   - [Fiabilité de TCP](#b-fiabilité-de-tcp)
   - [Format des messages TCP](#c-format-des-messages-tcp)
   - [Contrôle de flux](#d-contrôle-de-flux)
   - [Contrôle de congestion](#e-contrôle-de-congestion)
5. [Comparaison entre UDP et TCP](#5-comparaison-entre-udp-et-tcp)
6. [Questions](#6-questions)

---

## 1. Introduction
La **couche transport** assure la communication logique entre processus d'applications s'exécutant sur des hôtes différents. Elle garantit la communication **de bout en bout** en récupérant les données de la couche application et en les transmettant à la couche réseau.

- La couche transport divise les données applicatives en **segments**.
- Elle prend en charge deux types de protocoles : **UDP** et **TCP**.

### Responsabilités de la couche transport :
- **Multiplexage/Démultiplexage** : Gestion de plusieurs canaux de communication sur une connexion réseau unique.
- **Fiabilité** : Assure une livraison correcte des paquets dans le bon ordre (comme avec TCP).
- **Contrôle de congestion** : Gère la charge du trafic sur le réseau.

---

## 2. Principes généraux de la couche transport
La couche transport communique avec la **couche application** et la **couche réseau**.

- **TCP** (Transmission Control Protocol) : Protocole orienté connexion offrant une communication fiable.
- **UDP** (User Datagram Protocol) : Protocole sans connexion, rapide mais sans garantie de livraison.

**Schéma ASCII : Couche Transport dans la pile réseau**
```
  +------------------------+
  |    Couche Application   |
  +------------------------+
  |    Couche Transport     | <--- Fonctionnement des protocoles TCP/UDP
  +------------------------+
  |    Couche Réseau        |
  +------------------------+
```

---

## 3. UDP (User Datagram Protocol)

### a) Introduction à UDP
- **Protocole sans connexion** : Aucune connexion n'est établie avant l'envoi des données.
- **Best-effort delivery** : Ne garantit pas la livraison, ni l'ordre, ni la correction d'erreurs.
- Utilisé dans les applications nécessitant une **faible latence** (ex : streaming, VoIP).

### b) Format des messages UDP
Les messages UDP comportent quatre champs :
- **Port Source** : Port de l'expéditeur.
- **Port Destination** : Port du récepteur.
- **Longueur** : Longueur totale du segment UDP.
- **Checksum** : Mécanisme de vérification d'erreurs pour l'intégrité des données.

**Schéma ASCII : Format de l'en-tête UDP**
```
  +--------------------------------------------------------+
  |  Port Source  |  Port Destination  |  Longueur  |  Checksum  |
  +--------------------------------------------------------+
  |                    Données applicatives (payload)                    |
  +--------------------------------------------------------+
```

### c) Résumé UDP
- **Avantages** : Simple, faible surcharge, rapide.
- **Inconvénients** : Pas de garantie de livraison, pas de contrôle de flux ni de congestion.
- **Cas d'utilisation** : Streaming multimédia, jeux en ligne, requêtes DNS.

---

## 4. TCP (Transmission Control Protocol)

### a) Introduction à TCP
- **Protocole orienté connexion** : Nécessite l'établissement d'une connexion avant le transfert de données.
- **Livraison fiable** : Garantit que les données arriveront dans le bon ordre, avec correction des erreurs et retransmission des segments perdus.

### b) Fiabilité de TCP
TCP utilise plusieurs mécanismes pour garantir la fiabilité :
- **ACKs (Accusés de réception)** : Envoyés par le récepteur pour confirmer la réception des segments.
- **Timeouts** : Si un accusé de réception n'est pas reçu dans un délai donné, le segment est retransmis.
- **Numérotation des segments** : Assure que les données sont livrées dans le bon ordre.

**Schéma ASCII : Protocole Stop-and-Wait**
```
  Émetteur        Récepteur
  [Envoi de Paquet] --> 
                 <-- [ACK]
  [Envoi de Paquet] -->
                 <-- [ACK]
```

### c) Format des messages TCP
Les segments TCP comportent plusieurs champs pour assurer une communication fiable :
- **Numéro de séquence** : Identifie la position du segment dans le flux de données global.
- **Numéro d'accusé de réception** : Indique le prochain octet que le récepteur s'attend à recevoir.
- **Flags de contrôle** : Comprend SYN (établir la connexion), FIN (terminer la connexion), ACK (accusé de réception), etc.
- **Taille de fenêtre** : Indique la quantité de données que le récepteur peut accepter.

**Schéma ASCII : Format de l'en-tête TCP**
```
  +-------------------------------------------------------+
  |  Port Source  |  Port Destination  |  Numéro de Séquence |
  +-------------------------------------------------------+
  |  Numéro d'Accusé de Réception  |  Flags  |  Taille de Fenêtre |
  +-------------------------------------------------------+
  |                  Données applicatives (payload)                  |
  +-------------------------------------------------------+
```

### d) Contrôle de flux
TCP utilise un mécanisme de **fenêtre glissante** pour réguler la quantité de données envoyées avant qu'un accusé de réception ne soit requis. La **fenêtre de réception** (rwnd) permet d'éviter la surcharge des tampons du récepteur.

**Schéma ASCII : Mécanisme de la fenêtre glissante**
```
  Émetteur                   Récepteur
  [Paquet 1] -->         [Espace Tampon]
  [Paquet 2] -->         [ACK Paquet 1]
  [Paquet 3] -->         [ACK Paquet 2]
```

### e) Contrôle de congestion
TCP inclut des mécanismes pour éviter la congestion :
- **Démarrage lent (Slow Start)** : Augmente progressivement le taux de transmission jusqu'à la détection d'une perte de paquet.
- **Évitement de congestion** : Une fois une perte détectée, la taille de la fenêtre est réduite pour contrôler la congestion.

**Schéma ASCII : Contrôle de congestion**
```
  Temps
  |
  |      /\
  |     /  \    <-- Démarrage lent
  |    /    \
  |   /      \  <-- Évitement de congestion
  +------------------->
       Taille de la fenêtre de congestion
```

---

## 5. Comparaison entre UDP et TCP

| Fonctionnalité             | UDP                                  | TCP                             |
|----------------------------|--------------------------------------|---------------------------------|
| **Connexion**              | Sans connexion                       | Orienté connexion               |
| **Fiabilité**              | Pas de garantie de livraison          | Livraison fiable                |
| **Contrôle de flux**       | Aucun contrôle de flux               | Contrôle par fenêtre glissante  |
| **Contrôle de congestion** | Aucun contrôle de congestion         | Démarrage lent et évitement de congestion |
| **Cas d'utilisation**      | Streaming, DNS, Jeux en ligne        | Navigation web, transfert de fichiers |

---

## 6. Questions

1. **Quelle est la différence entre TCP et UDP en termes de fiabilité ?**
2. **Expliquez le mécanisme de la fenêtre glissante dans TCP.**
3. **Pourquoi utilise-t-on le démarrage lent dans le contrôle de congestion TCP ?**
4. **Quels sont les quatre champs d'un en-tête UDP ?**
5. **Comment TCP garantit-il l'ordre correct des paquets ?**
6. **Dans quel scénario UDP serait-il préféré à TCP ?**

