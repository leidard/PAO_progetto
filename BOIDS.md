# Boids

## Table of Contents

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
