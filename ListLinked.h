#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <stdexcept>
#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
        Node<T>* first;
	int n;

    public:

        ListLinked () {
		first = nullptr;
		n = 0;
	}

	~ListLinked() {
            while (first != nullptr) {
                Node<T>* aux = first->next;
                delete first;
                first = aux;
            }
        }

        T operator[](int pos) {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición inválida!");
            }
            Node<T>* aux = first;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data;
        }

        friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            out << "List => [\n";
            Node<T>* aux = list.first;
            while (aux != nullptr) {
                out << "  " << aux->data << "\n";
                aux = aux->next;
            }
            out << "]";
            return out;
        }

	void insert(int pos, T e) override {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición inválida!");
            }
            if (pos == 0) {
                first = new Node<T>(e, first);
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                prev->next = new Node<T>(e, prev->next);
            }
            n++;
        }

        void append(T e) override {
            insert(n, e);
        }

        void prepend(T e) override {
            insert(0, e);
        }

        T remove(int pos) override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición inválida!");
            }
            
            Node<T>* aux = first;
            T data;

            if (pos == 0) {
                first = first->next;
            } else {
                Node<T>* prev = first;
                for (int i = 0; i < pos - 1; i++) {
                    prev = prev->next;
                }
                aux = prev->next;
                prev->next = aux->next;
            }

            data = aux->data;
            delete aux;
            n--;
            return data;
        }

        T get(int pos) const override {
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición inválida!");
            }
            Node<T>* aux = first;
            for (int i = 0; i < pos; i++) {
                aux = aux->next;
            }
            return aux->data;
        }

        int search(T e) const override {
            Node<T>* aux = first;
            for (int i = 0; i < n; i++) {
                if (aux->data == e) {
                    return i;
                }
                aux = aux->next;
            }
            return -1;
        }

        bool empty() const override {
            return n == 0;
        }

        int size() const override {
            return n;
        }


};

#endif

