<b>Opis ogólny</b><br>
Projekt "Saper" to gra polegająca na odnajdywaniu min na planszy. Gra jest napisana w C++ z wykorzystaniem biblioteki SFML do grafiki i obsługi zdarzeń.<br><br>

<b>Wygląd gry</b><br>
![380739112_1261963997801798_5811632103275220907_n](https://github.com/MrDemolish/Saper/assets/147986097/aff09d0e-8829-48b1-9180-58fd8a4242cf)


<b>Wymagania</b><br>
<ul>
  <li>C++11 lub nowszy</li>
  <li>Biblioteka <a href="https://www.sfml-dev.org/download/sfml/2.6.0/">SFML 2.6.0</a></li>
  <li>System operacyjny zgodny z Windows (z powodu użycia funkcji Sleep())</li>
  <li>Przeniesienie folderu "res" do folderu w którym znajduje się skompilowana gra</li>
</ul>

<b>Zawartość folderu</b><br>
![image](https://github.com/MrDemolish/Saper/assets/147986097/4a0752aa-04c9-465f-b3de-a446b1e14e88)


<b>[Struktura kodu]</b><br>
<b>Stałe i zmienne globalne</b><br>
<ul>
  <li>BOARD_SIZE: Rozmiar planszy.</li>
  <li>CELL_SIZE: Rozmiar jednej komórki na planszy.</li>
  <li>MINES: Liczba min na planszy.</li>
  <li>MINE i EMPTY: Stałe do oznaczenia miny i pustej komórki.</li>
  <li>board, revealed, flagged, questionMarked: Tablice przechowujące stan planszy i komórek.</li>
  <li>font: Font używany w grze.</li>
</ul>
<b>Prototypy funkcji</b><br>
<ul>
  <li>initializeBoard(): Inicjalizuje planszę.</li>
  <li>reveal(int x, int y): Odkrywa komórki.</li>
  <li>checkForGameEnd(sf::RenderWindow& window): Sprawdza, czy gra się zakończyła.</li>
  <li>handleMouseClick(int x, int y, sf::Mouse::Button button): Obsługuje kliknięcia myszą.</li>
</ul>
<b>Funkcje</b><br>
<b>initializeBoard()</b><br>
Inicjalizuje planszę, umieszcza miny i liczby w komórkach.<br><br>
<b>reveal(int x, int y)</b><br>
Odkrywa komórkę o podanych współrzędnych (x, y) i, jeśli jest pusta, odkrywa również jej sąsiadujące komórki.<br><br>
<b>checkForGameEnd(sf::RenderWindow& window)</b><br>
Sprawdza, czy gracz wygrał lub przegrał, i odpowiednio zamyka okno gry.<br><br>
<b>handleMouseClick(int x, int y, sf::Mouse::Button button)</b><br>
Obsługuje kliknięcia myszą, umożliwiając oznaczenie komórki flagą, znakiem zapytania lub odkrycie jej.<br><br>
<b>Główna pętla programu</b><br>
Pętla główna programu zarządza grafiką i zdarzeniami. Rysuje planszę i elementy gry w oknie, a także obsługuje zdarzenia takie jak kliknięcia myszą.<br>
