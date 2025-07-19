# parray

Ein "normales" Array könnte man als Potenz-Array bezeichnen, denn der
Speicherbedarf ergibt sich aus dem Produkt der Größen der einzelnen
Dimensionen, und wenn diese alle gleich sind, als Potenz dieser Größe K
hoch der Anzahl der Dimensionen N: K<sup>N</sup>. Bei N = 3 und K = 8 sind das
8<sup>3</sup> = 512 Speicherplätze.

Ein Parray<N,K> (Pascalsches Array) dagegen benötigt nur $\binom{N+K-1}{K-1}$
Speicherplätze. Analog zum obigen Beispiel benötigt ein Parray<3,8> also
$\binom{3+8-1}{8-1}$ = 120 Speicherplätze, also weniger als ein Viertel.

Mit zunehmendem N wird die Einsparung immer größer. Bei <20,10> braucht man
für die gigantische Menge eines Potenz-Arrays nur noch ca. 10 Millionen
Einträge, was locker in den Hauptspeicher eines Computers passt.

Erkauft wird das dadurch, dass die Indices eines Parray nicht beliebig
gewählt werden dürfen. Es gilt folgende Einschänkung: Die Summe der
(nur positiven) Indices muss immer N ergeben.

Das ist beispielsweise gegeben, wenn man bei einer N-stelligen Zahl die
Vorkommen der K verschiedenen Ziffern zählt.

Das Parray kommt auch aus der Kombinatorik. Es wird dort eingesetzt, um
theoretische Überlegungen praktisch schnell überprüfen zu können.
