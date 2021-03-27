# INSTRUKCJA PRACY Z REJESTRAMI DLA AVRxxxDBxx

## Najważniejsze informacje 
- mikrokontrolery z serii AVRxxxDBxx kożysatją z systemu rejestrów zorganizowanych w struktory 
- istnieje jeden typ identyczny struktury dla danego peryferium skopiowany dla każdej instancji danego peryferium
- aby zmienić wartości bitów w rejestrach wykorzystujemy komende INSTANCJA.REJESTR = 1 << MASKA POZYCJA BITU;
np. PORTA.DIRSET = 1 << PIN1_bp;    (opcja preferowana)
- alternatywą jest wykorzystanie komend 
  - dla ustawienia bitu: INSTANCJA.REJESTR = MASKA BITOWA;          NP. PORTA.OUT = PIN7_bm;
  - dla skasowania bitu: INSTANCJA.REJESTR &= ~(MASKA BITOWA);      NP. PORTA.OUT &= ~(PIN7_bm);
- w przypatku przygotwanych przez producenta makr ustawianie bitu w rejestrze(jeżeli takie makro istnieje zaleca się ich urzywanie dla wygody programisty): INSTANCJA.REJESTR = MAKRO;
np. BOD.INTCTRL = BOD_VLMCFG_FALLING_gc;
- W przypatku timera A należy pamiętać że istneją dwie różne od siebie struktury rejestrów używane zależnie od trybu pracy timera (single i split) i trzeba pamitać io tymm podając adres rejestru w operacjach zmiany bitów w tym ejestrze np tak: 
  -TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc;

## UWAGA POERACJE NA REJSTRACH IO ZOSTAŁY OPISANE W INNYM DOKUMENCIE





