(defun ex1 ()
    (lambda (l) (cons (car l) (cdr l))) '(1 2 3)
)

(defun ex2 ()
    ((lambda (l1 l2) (append l1 l2)) '(1 2) '(3 4))
)

;; functie care primese ca parametru o lista neliniara
;; NIL - daca lista are cel putin un atom numeric la nivel superficial
;; T - daca nu are un atom numeric la nivel superficial
(defun f (l)
    (cond
        ((null l) T)
        (((lambda (v)
            (cond
                ((numberp v) T)
                (t nil)
            )
        ) (car l)) nil) ;; daca functia lambda returneaza T, adica daca exista 
                        ;; atom numeric, va returna NILL / FALSE
        (t (f (cdr l)))
    )
)

;; FORMA LABELS
(defun ex3 () 
    (labels (
            (fct (l)
                (cdr l)
            )  
        )
        (fct '(1 2))
    )
)

(defun ex4 () 
    (labels (
        (temp (n)
            (cond
                ((= n 0) 0)
                (t (+ 2 (temp (- n 1))))
            
            )
        )
    ) (temp 3) )
)


;; functie care primeste ca parametru o liste de liste formate din atomi
;; T - daca toate listele contin atomi numerici
;; NIL - in caz contrar

(defun test (l)
    (cond
        ((null l) t)
        (
            (labels
                (
                    (test1 (l)
                        (cond
                            ((null l) T)
                            ((numberp (car l)) (test1 (cdr l)))
                            (t nil)
                        )
                    )
                )
                (test1 (car l))
            )
            (test (cdr l))
        )
        (t nil)
    )
)

;; UTILIZAREA EXPRESIILOR LAMBDA PENTRU EVITAREA APELURILOR REPETATE
(defun g (l)
    (cond
        ((null l) nil)
        (t (cons 
            (car (f l)) 
            (cadr (f l)))
        )
    )
)

;; VARIANTA 1
(defun g1(l)
    (cond
        ((null l) nil)
        (t (
            (lambda (v)
                (cons (car v) (cadr v))
            ) (f l))
        )
    )
)

;; VARIANTA 2
(defun g2 (l)
    ((lambda (v)
        (cond
            ((null l) nil)
            (t (cons (car v) (cadr v)))
        )
     ) (f l)
    )
)

;; functie care genereaza lista submultimilor unei multimi 
;; reprezentate sub forma de lista

(defun insPrimaPoz(e l)
    (cond 
        ((null l) nil)
        (t (cons 
                (cons e (car l)) 
                (insPrimaPoz e (cdr l))
           )
        )
    )
)

(defun subm (l)
    (cond
        ((null l) (list nil))
        (t (append 
            (subm (cdr l)) 
            (insPrimaPoz (car l) (subm (cdr l)))
           )
        )
    )
)

(defun subm_improved (l)
    (cond
        ((null l) (list nil))
        (t ((lambda (s)
                (append s (insPrimaPoz (car l) s))
            ) (subm (cdr l))   
           )
        )
    )
)

