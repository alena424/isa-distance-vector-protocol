# ISA Nástroje monitorující a generující zprávy jednoduchých distance-vector protokolů (Dr. Veselý) 

@autor Alena Tesarova
@email xtesar36@stud.fit.vutbr.cz

*Zadání*
1) nastudovat si směrovací protokoly RIP a RIPng
2) naprogramovat sniffer RIPv1, RIPv2 a RIPng zpráv
3) naprogramovat podvrhávač falešných RIPng Response zpráv
4) za použití obou nástrojů, které jste si předpřipravili v předchozím bodě pak provést úspěšný útok 

*RIP sniffer*
spuštění programu příklad:
./myripsniffer -i <rozhraní> 

-i: <rozhraní> udává rozhraní, na kterém má být odchyt paketů prováděn. 

Sniffer používá k odchytávání paketů filtr na udp port 520 a udp port 521. V nekonečné smyčce parsuje a vypisuje pakety na výstup. Ukončení CTRL + C.

*RIP response*
./myripresponse -i <rozhraní> -r <IPv6>/[16-128] {-n <IPv6>} {-m [0-16]} {-t [0-65535]}, kde význam parametrů je následující: 
* -i: <rozhraní> udává rozhraní, ze kterého má být útočný paket odeslán;
* -r: v <IPv6> je IP adresa podvrhávané sítě a za lomítkem číselná délka masky sítě;
* -m: následující číslo udává RIP Metriku, tedy počet hopů, implicitně 1;
* -n: <IPv6> za tímto parametrem je adresa next-hopu pro podvrhávanou routu, implicitně ::;
* -t: číslo udává hodnotu Router Tagu, implicitně 0.

Program odešle jeden paket podle hodnot, které byly předány na vstupu nebo použije defaultní hodnoty. Struktura odpovídá struktuře RIPng paketu popsaného v dokumentaci.

*Rozšíření*
Nebyla impelmentována žádná rozšíření k projektu.

===================================================
