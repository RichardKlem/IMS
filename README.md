# IMS
IMS projekt 2020

## Členové
Martin Haderka - xhader00
Richard Klem - xklemr00

## Zadání
**Téma č. 1: Epidemiologické modely pomocí celulárních automatů**<br/>
Model musí být implementován jako celulární automat. Model musí vycházet z konkrétní studie publikované ve vědeckém<br/>
časopise o konkrétní epidemii. Modely na úrovni "hra life" budou penalizovány.

## Referenční literatura
Z této literatury jsme čerpali informace, na kterých jsme pak stavěli svoji práci.<br/>

http://www.romjist.ro/full-texts/paper651.pdf?fbclid=IwAR36Y5RT4PkjhvZEQpI39UGmaAO-CGddzkyWMM2RQQMnyN9DF5u4Zt1A4fk

## Překlad
- `make`
Pro bezproblémový překlad použijte překladač podporující standard C++ 17.
## Spuštění
- `make run`
nebo
`./covid [volitelné argumenty]`<br/>
  
Program obsahuje základní nastavení na experiment číslo 2 dle článku, model 1.

## Parametry programu
- `-h` | `--help` : Zobrazí nápovědu.
- `-n` | `--number <uint>`: Celkový počet lidí.
- `-i` | `--infected <uint>`: Počáteční počet nakažených jedinců.
- `-m` | `--immune <uint>`: Počáteční počet imunních jedinců.
- `-x` | `--row <uint>`: První dimenze/počet řádků prostoru.
- `-y` | `--col <uint>`: Druhá dimenze/počet sloupců prostoru.
- `-s` | `--time-step <uint>`: Krok, se kterým se vypisují data za matice prostoru.
- `-f` | `--forward-p <uint>`: Pravděpodobnost pohybu osoby dopředu.
- `-b` | `--back-p <uint>`: Pravděpodobnost pohybu osoby dozadu.
- `-r` | `--right-p <uint>`: Pravděpodobnost pohybu osoby doprava.
- `-l` | `--left-p <uint>`: Pravděpodobnost pohybu osoby doleva.
- `-z` | `--stay-p <uint>`: Pravděpodobnost setrvání osoby na místě.
- `-d` | `--dump_dir <nazev slozky>`: Název složky, kam se generují soubory s daty z matice <br/>
prostoru a soubor s celkovým počtem cyklů.<br/>
                        POZOR! Složka musí existovat už před spuštěním programu!
- `-2` | `--model2` : Pokud je parametr zadán, použije se model 2. Pokud zadán není, pak<br/>
                se použije model číslo jedna. Více o modelech viz dokumentace.

Krátké parametry je možné zadávat ve tvaru `-n5` anebo `-n 5`.<br/>
Dlouhé parametry je nutné zadávat ve tvaru `--num=5`.<br/>
Program obsahuje základní nastavení na experiment číslo 2 dle článku, model 1.<br/>

## Doplňkové skripty
Oba doplňkové skripty vyžadují **Python3**. Závislosti si pak obstarávají sami.
### Automatizované experimenty
Skript spustí a zpracuje výslekdy ze 10 simulací každého z 20 předpřipravených experimentů.<br/>
Počet opakování lze upravit přímo v skriptu na řádku 63.<br/>
Pokud si nepřejete generovat všechny data ze simulátoru,<br/> 
pak zvolte vysokoou hodnotu kroku výpisu, například 1000 `--step=1000`.
#### Spuštění
- `make all_exp`
Skript vygeneruje HTML tabulku. Soubor se jmenuje `agregated_results.html`.
### Vizualizace průběhu simulace
Spustí se vizualizace experimentu definovaného jako základní v souboru `main.cpp`.<br/>
V základním nastavení se jedná o experiment 2 z článku. Více viz dokumentace.
#### Spuštění
- `make visualize`