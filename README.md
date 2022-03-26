# Aquarius

<!-- ![Logo](./assets/logo.svg) -->

## Sommario

Simulatore di un ambienete dove diversi organismi interagiscono tra di loro.
In particolare, sono stati scegli degli organismi marini.

## Vect2D

La classe Vect2D rappresenta un vettore a due dimensioni con le operazioni necessarie per effettuare tutti i calcoli dietro ogni spostamento dei veicoli all'interno dell'ambiente.
Ha una parte di funzioni non costanti che ritornano il riferimento alla classe stessa in modo da poter chiamare funzioni a catena.
Le stesse sono disponibili anche in versione costante per quando l'oggetto è costante e ritornerà quindi un nuovo oggetto per valore, mantenendo la possibilità di poter chiamare funzioni a catena con il ritorno.
Sempre le stesse funzioni sono disponibili in formato statico con ritorno per valore.
Effettua overload degli operatori aritmetici, che fanno da tramite per funzioni all'interno della classe.
Effettua overload degli operatori di comparazione.

## Gerarchia

![Gerarchia](./assets/gerarchia.png)

## Descrizione delle chiamate polimorfe

### Veicolo

```cpp
// distruttore virtuale di default, inutile ripeterlo
virtual void behaviour(Acquario*) = 0;
virtual bool isInRange(const Vect2D& v) const = 0;
virtual void advance(Aquarius* a, int phase) final;
```

### Organismo

```cpp
virtual void behaviour(Acquario*);
virtual bool isInRange(const Vect2D& v) const ;
virtual bool canSleep() const;
virtual bool canWakeup() const;
virtual bool isHungry() const = 0;
virtual int getValoreNutrizionale() const = 0;
```

## Note

Per maggiori dettagli riguardo al funzionamento dei veicoli all'interno della simulazione: [Boids.md](./BOIDS.md)

## Requisiti di progetto

-   almeno 3 tipi diversi istanziabili;
-   almeno una classe astratta;
-   gerarchia con altezza almeno 2;
-   container C a scelta (list, dlist, dqueue, queue, vector, ecc.);
-   puntatore smart (deep copy, assignemnt, deconstructor) puntatori polimorfi a T che suppportano clonazione e distruzione profonda;
-   utilizzo del contenitore C per uno dei tipi della gerarchia incapsulati dentro al puntatore smart;
-   funzionalità di input/output.
