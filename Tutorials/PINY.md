# INSTRUKCJA PRACY Z PORTAMI IO DLA AVRxxxDBxx

## operacje na kierunku pinu
- głównym rejestrem odpowiedzialnym za kierunek pinów jest PORTx.DIR
- jednak w celu ustawienia kierunku możemy wykorzystać rejestry pośrednie DIRSET, DIRCLR, DIRTGL 
    - PORTx.DIRSET = PINx_bm; dla ustawienia pinu na wyjście
    - PORTx.DIRCLR = PINx_bm; dla ustawienia pinu na wejście
    - PORTx.DIRTGL = PINx_bm; dla zmiany stanu kierunku pinu

## operacje na stanie pinu
- głównym rejestrem odpowiedzialnym za kierunek pinów jest PORTx.OUT
- jednak w celu ustawienia stanu możemy wykorzystać rejestry pośrednie DIRSET, DIRCLR, DIRTGL 
    - PORTx.OUTSET = PINx_bm; dla ustawienia pinu na stan wysoki
    - PORTx.OUTCLR = PINx_bm; dla ustawienia pinu na stan niski
    - PORTx.OUTTGL = PINx_bm; dla zmiany stanu na przecwny

## operacja odczytu stanow pinow
- głównym rejestrem przeznaczonym do odcztu jest PORTx.IN


## dodatkowe funkcje pinow
- indywidualny dla każdego pinu rejestr (PORTx.PINnCTRL) - po więcej informacji patrz dokumentacja


