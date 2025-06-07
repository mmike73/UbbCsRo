(defun atoms-mirrored (l)
  (cond
    ((null l) nil)  ; Dacă lista este goală, returnăm nil
    ((atom l) l)    ; Dacă este un atom, îl returnăm ca atare
    (t              ; Dacă este o listă
     (append (atoms-mirrored (cdr l))  ; Oglindim restul listei
             (list (atoms-mirrored (car l)))))))  ; Oglindim primul element