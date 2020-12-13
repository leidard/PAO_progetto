# Aquarius

Crea il tuo acquario customizzandolo con i pesci che preferisci, noi offriamo 3 pesci 
il pesce a livello 1 è impaurito e vuole solo allontanarsi da chi gli si avvicina
il pesce a livello 2 combatte la paura e, curioso, quando qualcuno gli si avvicina non scappa ma mantiene comunque sempre le distanze, e poi continua per la sua direzione
il pesce a livello 3 invece vive bene in branco e quando si avvicina qualcuno si allinea alla sua direzione e procede
Se si preferisce un pesce può ottenere un nome, fin dalla creazione oppure più tardi.
Ogni pesce ha un ciclo di movimento ossia dorme e sta fermo, poi si sveglia, comincia a muoversi e mangia il cibo che trova (mirando verso il cibo quando lo trova)
quando ha mangiato a sufficienza quando decide (magari dopo qualche minuto) può fermarsi e tornare a dormire.\
\
Pensavo che comunque possiamo definire anche senza per forza pesci di diverso livell.
Possiamo definire 2/3 categorie di pesci diverse che non so magari hanno una caratteristica in più o parametri di movimento particolari, magari cicli di sonno diversi, 
magari hanno bisogno di diverso tipo di cibo, magari quel cibo sono altri pesci di altro tipo (il che non risulta complicatissimo fa tutto l'algoritmo).
Magari queste categorie sono pesci plankton tipo che possiamo considerarli erbivori o che mangiano che ne so il cibo che gli da l'utente, e poi ci sono i carnivori che 
non mangiano tanto ma mangiano altri pesci plankton e solo quelli. E prendendo queste due categorie diverse si creano uno o più figli diversi per ciascuno.
Q
uindi per riassumere
|Altezza|    |
|----|----|
|0 | pesce astratto con magari istinti naturali???|
| 1| pesce carnivoro pesce erbivoro |
| 2| squalo(carnivoro) plantkon, sardine(erbivoro) |

## Istinti Naturali
Questi istinti naturali prevalgono su qualsiasi decisione dei livelli successivi del pesce, in quanto sono essenziali e determinano la salute del pesce
(dovremmo come creare una variabile semaforo)

### Food
Se nella area visiva del pesce compare del cibo (il cibo ha una traiettoria dall'alto verso il basso con caduta costante, il pesce se affamato curva nella direzione del cibo

### Obstacles
Se nella zona coompaiono degli ostacoli, controllare che la direzione attuale non miri verso l'ostacolo, in tal caso correggerla in modo che curvi per non andarci contro

### Movimenti random
Il pesce quando in movimento poichè è sempre curioso compie dei microspostamenti random (anche per creare delle cose visivamente simpatiche)

## Livelli Superiori

- ### Separation (lvl 1)
![Separation](https://www.red3d.com/cwr/boids/images/separation.gif)\
steer to avoid crowding local flockmates

- ### Cohesion
![Cohesion](https://www.red3d.com/cwr/boids/images/cohesion.gif)\
curva per muoversi nella posizione media dei boid

- ### Alignment
![Alignment](https://www.red3d.com/cwr/boids/images/alignment.gif)\
steer towards the average heading of local flockmates

## Azioni utente
utente puó scegliere quali e quanti pesci.
vista analitica dietro le quinte di cosa pensa cosa fa un pesce
cambiare parametri del campo visivo del pesce, o altre robe.
Puó nutrire manualmente oppure in automatico.

<hr/>
#### Sources
 - ![https://www.red3d.com/cwr/boids/](https://www.red3d.com/cwr/boids/)
