# Fondements des Réseaux - Detailed Recap

## Sommaire
1. [Qu'est-ce qu'Internet?](#1-quest-ce-quinternet)
2. [Structure de l’Internet](#2-structure-de-linternet)
   - [Réseau de Bordure](#a-réseau-de-bordure)
   - [Réseau de Cœur](#b-réseau-de-cœur)
3. [Performance des Réseaux](#3-performance-des-réseaux)
4. [Modèles de Normalisation des Réseaux](#4-modèles-de-normalisation-des-réseaux)
   - [Modèle OSI](#a-modèle-osi-7-couches)
   - [Modèle Internet](#b-modèle-internet-tcpip)
5. [Sécurité des Réseaux](#5-sécurité-des-réseaux)
6. [Questions Importantes](#questions-importantes)

---


## 1. Qu'est-ce qu'Internet?

- **Internet** : "Réseau de réseaux" reliant des millions d'appareils.
- **Hôtes ou Terminaux** : Ordinateurs, smartphones exécutant des applications (Web, email, etc.).
- **Liens de communication** : Fibre optique, câble, radio, satellite avec des différences de débit (bande passante).

### ASCII Schema : Vue Matérielle de l'Internet

```plaintext
       [Terminal 1] 
          |
   -------|---------                  ------- Internet Service Provider -------
   |      |         |                 |                                         |
[Fibre] [Cable] [Satellite]   ->   [ISP Local] -- [ISP Global] -- [Data Center]
                                       |                                         |
                                     [Access Network]                   [Core Network]
```
- **Protocole** : Un protocole définit le format, l'ordre des messages échangés et les actions en réception/transmission (ex: TCP/IP).

## 2. Structure de l'internet

### a) Réseau de Bordure

- **Terminaux** :  Hôtes et serveurs exécutant des applications comme le WWW et email.
- **Réseaux d'accès** :
	- **DSL** : Utilise les lignes téléphoniques, débit descendant 52 Mb/s.
	- **FTTH** : FIbre optique jusqu'à 10 Gb/s

### b) Réseau de Coeur
- **Commutation** : Transfert de paquets de données via des routeurs interconnectés.
- **Routage** : Détermination du chemin entre la source et la destination

### ASCII Schema : Structure de l'Internet

```plaintext
  [Terminal] --- [Access Network] --- [ISP Local] --- [Core Network] --- [Data Center]
                      |                                             |
                [WiFi, DSL]                                  [Router, Switch]
```

## 3. Performance des Réseaux

- **Délai** : Temps total pour qu'un paquet aille de l'émetteur au récepteur.
	- **dproc** : Délai de traitement.
	- **dqueue** : Délai en file d'attente.
	- **dtrans** : Délai de transmission (L/R).
	- **dprop** : Délai de propagation (distance/vitesse du signal).

### ASCII Schema : Composants du Délai

```plaintext
   [dproc] -> [dqueue] -> [dtrans] -> [dprop]
        |       |            |         |
  Vérif. d'erreur File d'attente Transmission Propagation
```

- **Débit** : Quantité de données transférées par unité de temps.
- **Perte de paquets** : Paquets supprimés si la mémoire du routeur est saturée.


## 4. Modèles de Normalisation des Réseaux

### a) Modèle OSI (7 Couches)
	1. **Physique** : Transmission de bits sur le support physique.
	2. **Liaison de données** : Transmission fiable entre deux noeuds.
	3. **Réseau** : Acheminement des paquets.
	4. **Transport** : Communication de bout en bout.
	5. **Session** : Gestion des connections.
	6. **Présentation** : Conversion des formats de données.
	7. **Application** : Interface pour les services réseau (HTTP, FTP).

### ASCII Schema : Modèle OSI

```plaintext
  -------------------------
  | Application (HTTP, FTP)|
  -------------------------
  | Présentation (Format)  |
  -------------------------
  | Session (Connexions)   |
  -------------------------
  | Transport (TCP, UDP)   |
  -------------------------
  | Réseau (IP, Routing)   |
  -------------------------
  | Liaison (Ethernet)     |
  -------------------------
  | Physique (Câbles)      |
  -------------------------
```

### b) Modèle Internet (TCP/IP)
	1. **Application** : Protocoles réseau (HTTP, FTP).
	2. **Transport** : Communication entre hôtes (TCP, UDP).
	3. **Réseau** : Routage des paquets (IP).
	4. **Liaison** : Communication entre réseaux voisins.
	5. **Physique** : Transmission des bits.

## 5. Sécurité des Réseaux

	- **Malware** : Virus, vers, spyware qui infectent des hôtes
	- **Attaques DoS (Denial of Service)** : Inondation de trafic pour rendre des ressources inaccessibles.
	- **Sniffing** : Capture de paquets sur un réseau (mots de passe, données sensibles).
	- **Spoofing** : Falsification de l'adresse IP pour imiter une source légitime.
### ASCII Schema : Attaque DoS

```plaintext
    [Botnet 1]      [Botnet 2]        [Botnet 3]     
        |               |                 |
   -----|---------------|-----------------|-----------
   |                                             |  
[Serveur Cible] ------------------------------- Overloaded 
```
	- **Lignes de Défense** :
		- **Pare-feu** : Filtrage des paquets.
		- **Cryptage** : Protection des données via des techniques de chiffrement.
		- **Authentification** : Vérification d'indentité (ex: carte SIM).

## Questions Importantes

	1. Quelles sont les couches du modèle OSI?
	2. Expliquez la différence entre la commutation de paquets et la commutation de circuits.
	3. Quels sont les principaux types d'attaques réseau?
	4. Comment le délai de propagation est-il calculé?

