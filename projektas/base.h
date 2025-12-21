#include <string>

using namespace std;

/**
 * @class Zmogus
 * @brief Bazinė abstrakti klasė, aprašanti žmogų su vardu ir pavarde.
 *
 * Ši klasė naudojama kaip pagrindas studentams ar kitiems asmenims.
 * Turi grynai virtualią funkciją info(), todėl negali būti sukurta tiesiogiai.
 */
class Zmogus {
protected:
    string vard; ///< Studento vardas
    string pav; ///< Studento pavardė
public:
    /**
     * @brief Konstruktorius su vardu ir pavarde.
     * @param v Vardas
     * @param p Pavardė
     */
    Zmogus(const string& v = "", const string& p = "") : vard(v), pav(p) {}

    /**
     * @brief Virtualus destruktorius.
     *
     * Leidžia saugiai naikinti objektus per bazinės klasės rodykles.
     */
    virtual ~Zmogus() {
        vard.clear();
        pav.clear();
    }

    /**
     * @brief Grąžina žmogaus vardą.
     * @return Vardas kaip string
     */
    string getVard() const { return vard; }
    /**
     * @brief Grąžina žmogaus pavardę.
     * @return Pavardė kaip string
     */
    string getPav() const { return pav; }

    /**
     * @brief Nustato žmogaus vardą.
     * @param v Naujas vardas
     */
    void setVard(const string& v) { vard = v; }
    /**
     * @brief Nustato žmogaus pavardę.
     * @param v Nauja pavardė
     */
    void setPav(const string& p) { pav = p; }

    /**
     * @brief Virtuali funkcija informacijai išvesti.
     *
     * Turi būti perrašyta išvestinėse klasėse.
     */
    virtual void info() const = 0;
};
