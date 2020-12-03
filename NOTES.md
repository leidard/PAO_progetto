# Progetto 1

## Requisiti

- [x] almeno 3 tipi diversi istanziabili
- [ ] almeno una classe astratta
- [ ] almeno altezza 2
- [ ] container C a scelta (list, dlist, dqueue, queue, vector, ecc...)
- [ ] puntatore smart (deep copy, assignemnt, deconstructor) puntatori polimorfi a t che suppportano clonazione e distruzione profonda
- [ ] utilizzo del contenitore C per uno dei tipi della gerarchia incapsulati dentro il puntatore smart
- [ ] input/output

## Partita

Tutto parte dall'avvio di una partita, viene quindi definita la tavola "board" e quindi i 32 pezzi ciascuno nella sua posizione iniziale. Viene definita anche la storia delle mosse per potere analizzare la partita.

1. All'avvio la Board chiede a tutti i pezzi **bianchi** le loro possibili mosse dato lo stato attuale della board
2. Bianco fa la prima mossa

    ```c
    Mossa m(posizione1, posizione2)
    Board.move(m)
    ```

3. Board cerca tra le sue mosse preventivamente create se é presente la mossa attuale e in tal caso procede all'esecuzione della mossa
4. La mossa viene elaborata dalla scacchiera, diventa quindi spostamento del puntatore della pedina mossa nella sua nuova posizione, e viene aggiunta permanentemente alla storia delle mosse
    - nel caso di mossa non valida non viene effettuato nulla.
    - nel caso di cattura di una pedina, la pedina viene spostata nella "prigione" del proprio colore.

## Board

Viene inizializzata creando le 32 pedine divise tra i due colori e diversi ruoli, ognuna verrá assegnato il suo posto all'interno della griglia.
La Board fará da tramite tra la partita e i pezzi.
Griglia di 64 caselle. Le caselle possono essere vuote se non occupate da un pezzo, oppure occupate se é presente un pezzo.
La Board alla creazione e dopo ogni mossa chiede a ciascun pezzo di generare la lista di mosse possibili identificate da la tupla (casella partenza, casella destinazione). Con particolare attenzione al Re, che quando in scacco deve essere liberato: saranno quindi solamente ammissibili mosse atte per liberarlo

## Prigione

Spazio Dove vengono depositate le pedine catturate, una per le pedine bianche, una per le nere. In questo modo da uno stato ad un altro della scacchiera vengono spostati riferimenti e non vengono mai eliminati nemmeno quando catturati.

## Pezzo

Pezzo é una classe astratta che viene poi estesa in tutti i vari tipi di pezzi della scacchiera (pedone, torre, cavallo, alfiere, re, regina). Il Pezzo ricevendo come input lo stato attuale della tavola e in base al suo tipo di mosse restituisce le sue possibili.

## Mosse

Viene distinta in Mossa, e derivata in MossaInAvanti.
La MossaAvanti una volta scelta come mossa dall'utente diventa una Mossa base utile per lo storico delle mosse.

### Mossa

Definisce la mossa con una stringa rappresentante la notazione di scacchi per l'utente ma tiene anche conto in modo programmatico della mossa effettuata.
source = e2;
destin = e4;

### MossaAvanti

É una mossa definita prima di essere effettuata, potrebbe contenere ulteriori informazioni come la sua importanza per la vittoria, o altro.
