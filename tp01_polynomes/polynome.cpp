#ifndef POLYNOME
#define POLYNOME
#include "monome.cpp"
#include <vector>
#include <algorithm>
#include <unordered_map>
typedef std::vector<Monome> MonoVec;
typedef std::vector<Monome>::iterator MonoVec_It; 
typedef std::vector<Monome>::const_iterator MonoVec_CIt;

using namespace std;

class Polynome
{
private:
	MonoVec data;
	static void simplify(MonoVec& data){
		MonoVec data_;
		for (auto v: data){
			if (v.coeff != 0){
				if (data_.size() && data_.back().degree  == v.degree){
					data_.back() = data_.back() + v;
				}
				else{
					data_.push_back(v);
				}
			}
		}
		data = data_;
	}

public:
	Polynome(int coeff = 0, unsigned degre = 0): data({Monome(coeff, degre)}) {}
	Polynome(const vector<int>& coeff, const vector<unsigned>& degre){
		int n = coeff.size();
		for (int i = 0; i < n; i++){
			Monome tmp(coeff[i], degre[i]);
			data.push_back(tmp);
		}
		sort(data.begin(), data.end());
		simplify(data);
	}

	Polynome(const MonoVec& data0): data(data0) {}

	Polynome operator+(const Polynome& other){
		Polynome ans = Polynome(this -> data);
		for (auto& v: other.data){
			ans.data.push_back(v);
		}
		sort(ans.data.begin(), ans.data.end()); // sort before print
		simplify(ans.data);
		return ans;
	}

	Polynome operator-(const Polynome& other){
		Polynome tmp = other;
		for (auto& v: tmp.data){
			v.coeff = -v.coeff;
		}
		Polynome ans = this -> operator+(tmp);
		simplify(ans.data);
		return ans;
	}

	Polynome operator+(const int& v){
		MonoVec data_ = data;
		Monome toadd(v, 0);
		data_.push_back(toadd);
		sort(data_.begin(), data_.end());
		simplify(data_);
		
		Polynome toR(data_);
		return toR;
	}

	Polynome operator-(const int& v){
		return this -> operator+(-v);
	}

	Polynome operator*(const Polynome& v){
		// fast FFT?
		Polynome cur = Polynome(this -> data);
		MonoVec ans;
		for (auto othermono = v.data.begin(); othermono != v.data.end(); ++othermono){
			for (auto thismono = cur.data.begin(); thismono !=cur.data.end(); ++thismono){
				Monome tmp;
				tmp.coeff = thismono->coeff * othermono->coeff;
				tmp.degree =  thismono->degree + othermono->degree; // why cannot thismono.degree ?
				ans.push_back(tmp);
			}
		}
		sort(ans.begin(), ans.end());
		simplify(ans);
		return ans;

	}

	friend ostream& operator<<(ostream& os, const Polynome& poly){
		int cnt = 0;
		for (auto mono: poly.data){
			if (cnt++ < poly.data.size() - 1) os << mono << " + ";
			else os << mono << endl;
		}
		return os;
	}

	~Polynome(){}
};

#endif