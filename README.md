# Aquarius

![Logo](./assets/logo.svg)

-   [Definizioni](#definizioni)
-   [Steering Behaviour](#steering-behaviour)
    -   [Step By Step](#step-by-step)
        -   [Step 1](#step-1)
        -   [Step 2](#step-2)
        -   [Step 3](#step-3)
        -   [Step 4](#step-4)
    -   [Completo](#completo)
-   [Flock Behaviour](#flock-behaviour)
-   [Sources](#sources)

## Definizioni

| Nome          | sinonimi                      | Definizione                                                                               |
| ------------- | ----------------------------- | ----------------------------------------------------------------------------------------- |
| Vettore       | Forza, Posizione nello Spazio | coppia di valori (x,y) possono rappresentare una posizione in uno spazio oppure una forza |
| Posizione     | Vettore Posizione             | coppia di coordinate nello spazio che rappresentano la posizione attuale del veicolo      |
| Velocitá      | Vettore Velocitá              | Variazione della posizione                                                                |
| Accelerazione | Vettore Accelerazione         | Variazione della velocitá                                                                 |
| Veicolo       | Boid                          | Oggetto che possiede una posizione e una velocitá e un determinato campo visivo           |
| Flock         | Stormo, Branco                | Gruppo di Veicoli                                                                         |

## Steering Behaviour

Una volta definito un target dobbiamo definire un comportamento per curvare lentamente verso di esso, creando un comportamento piú naturale e graduale.
Craig Reynolds definisce questo come "Steering Behaviour".
É importante introdurre inoltre quindi il concetto

> "Conosco lo stato attuale del veicolo (posizione, velocitá) e voglio andare verso il target **a massima velocitá**."

### Step By Step

#### Step 1

Calcolo la differenza tra la posizione del veicolo e del target, ottenendo un vettore che, visto dalla posizione attuale, punta fino al target.

```c++
// Vect2D position;
// Vect2D velocity;
// Vect2D target;
// double maxSpeed;
// double maxForce;
const Vect2D diff = (target - position)
```

#### Step 2

> "[...] voglio andare verso il target **a massima velocitá**."

Significa che devo limitare il vettore `diff` appena ottenuto ad una velocitá massima devo quindi impostare la "lunghezza" o "modulo" (in inglese Magnitude) ad un valore maxSpeed.

```c++
// double maxSpeed;
const Vect2D desired = desired.setMagnitude(maxSpeed);
```

`desired` corrisponde alla velocitá che potrei assumere nel prossimo step della animazione, ma voglio permettere l'interazione tra piú forze per determinare come curvare, e per di piú applicarlo direttamente significherebbe un comportamento troppo scattoso e innaturale. Basta pensare se il target fosse alle spalle del veicolo, questo significherebbe che in un singolo step il veicolo si girerebbe di 180 gradi, non é accettabile. Devo quindi trovare un modo diverso per curvare

#### Step 3

Voglio quindi calcolare di quanto dovrei modificare la velocitá **( = accelerazione)**. Questo si ottiene sottraendo alla velocitá desiderata `desired` la velocitá attuale `velocity`.

```c++
// Vect2D velocity;
const Vect2D acc = (desired - velocity)
```

Ottengo quindi l'accelerazione da sommare alla velocitá per curvare verso il nostro target. Ma se lo facessi senza altre alterazioni all'accelerazione risulterebbe nei problemi descritti prima.

#### Step 4

Il passaggio chiave sta nella limitazione della forza di accelerazione, come prima abbiamo fatto per la velocitá.
Masggiore é la maxForce e piú a pieno applico l'accelerazione risultando in una curva piú stretta per arrivare al target, minore é la maxFOrce e meno applico l'accelerazione risultando in una curva piú larga per arrivare al target

```c++
// double maxForce;
const Vect2d acclimited = acc.limit(maxForce);
```

Posso quindi combinare questa accelerazione, con altre derivate da diversi comportamenti, il risultato finale applicato alla velocitá risulterá in una combinazione di tutte queste forze.

### Completo

![seek](./assets/seek.gif)

```c++
// Vect2D position;
// Vect2D velocity;
// Vect2D target;
// double maxSpeed;
// double maxForce;
const Vect2D diff = (target - position)
const Vect2D desired = desired.setMagnitude(maxSpeed);
const Vect2D acc = (desired - velocity)
const Vect2d acclimited = acc.limit(maxForce);
```

Una volta definito questo comportamento si possono creare variazioni per casi particolari.

## Flock Behaviour

Un esempio di steering behaviour tra i piú noti e affascinanti é il "Flock Behaviour" descritto da Craig Reynolds nella sua [pubblicazione](https://www.red3d.com/cwr/boids/).

| Nome         | Rappresentazione                                                     | Descrizione                                                                                            |
| ------------ | -------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------ |
| Separazione  | ![Separation](https://www.red3d.com/cwr/boids/images/separation.gif) | Sterza per evitare di scontrarsi con gli altri componenti dello stormo                                 |
| Coesione     | ![Cohesion](https://www.red3d.com/cwr/boids/images/cohesion.gif)     | Sterza verso la posizione media degli altri componenti dello stormo                                    |
| Allineamento | ![Alignment](https://www.red3d.com/cwr/boids/images/alignment.gif)   | Sterza per allineare la sua direzione con la media delle direzioni degli altri componenti dello stormo |

## Sources

-   [Craig Reynolds](https://www.red3d.com/cwr/)
-   [Craig Reynolds's Steering Behaviour](https://www.red3d.com/cwr/steer/)
-   [Craig Reynolds's Boids And Flocking Behaviour](https://www.red3d.com/cwr/boids/)
-   [Nature Of Code](https://natureofcode.com/book/chapter-6-autonomous-agents/): guida piú aggiornata e dettagliata per implementare questi comportamenti.
    \
    \
    \
    \
    \
    \
    \
    \
    \
    \
    \
    \

# Old Notes

-   [x] almeno 3 tipi diversi istanziabili
-   [ ] almeno una classe astratta
-   [ ] almeno altezza 2
-   [ ] container C a scelta (list, dlist, dqueue, queue, vector, ecc...)
-   [ ] puntatore smart (deep copy, assignemnt, deconstructor) puntatori polimorfi a t che suppportano clonazione e distruzione profonda
-   [ ] utilizzo del contenitore C per uno dei tipi della gerarchia incapsulati dentro il puntatore smart
-   [ ] input/output

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
|Altezza| |
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

## Azioni utente

utente puó scegliere quali e quanti pesci.
vista analitica dietro le quinte di cosa pensa cosa fa un pesce
cambiare parametri del campo visivo del pesce, o altre robe.
Puó nutrire manualmente oppure in automatico.

### Behaviours

```
/**
    @returns tirevalue, value from 0 to 1 that tells how much is it tired
*/
double isTired();

```

-   (FOOD) flee from bigger ones
-   (FOOD) seek for smaller ones
-   (FISH) MIMETIZATION check if I can see the other fish by checking if random number is lower than or equal the mimetizzazione/visibility value

#### tipo1

-   (FISH) alone behaviour
-   (FISH) long awaketime and sleeptime
-   (FISH) aumento del sonno dopo ogni pasto in base alla dimensione del cibo mangiato

#### tipo2

-   (FISH) flock behaviour
-   (FISH) short awaketime and sleeptime
-   (FISH) letargo dopo X cycles of sleep/awake

<hr/>

### TODO

graphicsview
set anti aliasing QPainter::Antialiasing

QGraphicsScene a uno slot chiamato advance()
collegando un QTimer cosí
conenct(timer, SIGNAL(timeout()), scene, SLOT(advance()));
verrá chiamato l'advance nella scene che dirrá a tutti gli item di procedere nello step di animazione

-   craere un custom QGraphicsItem per ogni pesce e ogni cibo vegetale
    setflag items is movable (ItemIsMovable)
    deve essere cliccabile
    mousepress or even better mouse hover
    mouserelease
    mouse leave
    paint(QPainter\* painter, QStyleObject )
    boundingRect

per impostare la posizione setPos(mapToParent(0,-velocity));
per impostare la rotazione invece si usa il setRotation(angle) con angle in degrees NON radianti
