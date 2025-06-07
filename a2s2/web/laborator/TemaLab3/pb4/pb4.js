//h
function sorteazaRanduriPeColoana(tabel, colIndex) {
    const tbody = tabel.querySelector('tbody');
    const randuri = Array.from(tbody.rows);
    const asc = !tabel.dataset.sortAsc || tabel.dataset.sortCol != colIndex;

    randuri.sort((a, b) => {
      const va = a.cells[colIndex].textContent;
      const vb = b.cells[colIndex].textContent;
      const na = parseFloat(va);
      const nb = parseFloat(vb);
      const comp = isNaN(na) || isNaN(nb)
        ? va.localeCompare(vb)
        : na - nb;
      return asc ? comp : -comp;
    });

    randuri.forEach(r => tbody.appendChild(r));
    tabel.dataset.sortAsc = asc;
    tabel.dataset.sortCol = colIndex;
  }

  document.querySelectorAll('.tabel-sortabil').forEach(tabel => {
    const capTabel = tabel.querySelector('thead');
    capTabel.querySelectorAll('th').forEach((th, i) => {
      th.addEventListener('click', () => {
        sorteazaRanduriPeColoana(tabel, i);
      });
    });
  });
//v

function sorteazaColoanePeRand(tabel, randIndex) {
    const randuri = Array.from(tabel.rows);
    const header = randuri.map(r => r.cells[0]);
    const valori = randuri[randIndex].cells;

    // Construim array cu coloanele 1..n și valorile respective
    let coloane = [];
    for (let i = 1; i < valori.length; i++) {
      let coloana = [];
      for (let r = 0; r < randuri.length; r++) {
        coloana.push(randuri[r].cells[i]);
      }
      coloane.push({
        valoare: valori[i].textContent,
        celule: coloana
      });
    }

    // Detectăm dacă deja sortăm crescător și inversăm dacă da
    const asc = !tabel.dataset.sortAsc || tabel.dataset.sortRand != randIndex;
      coloane.sort((a, b) => {
        const va = isNaN(a.valoare) ? a.valoare : parseFloat(a.valoare);
        const vb = isNaN(b.valoare) ? b.valoare : parseFloat(b.valoare);
        return asc ? (va > vb ? 1 : -1) : (va < vb ? 1 : -1);
      });

      // Reordonăm celulele în tabel
      for (let r = 0; r < randuri.length; r++) {
        for (let i = 0; i < coloane.length; i++) {
          randuri[r].cells[i + 1].textContent = coloane[i].celule[r].textContent;
        }
      }

      tabel.dataset.sortAsc = asc;
      tabel.dataset.sortRand = randIndex;
    }

    document.querySelectorAll('.tabel-sortabil').forEach(tabel => {
      const randuri = Array.from(tabel.rows);
      randuri.forEach((rand, i) => {
        const primaCelula = rand.cells[0];
        primaCelula.addEventListener('click', () => {
          sorteazaColoanePeRand(tabel, i);
        });
      });
    });