#pragma once

#include "TimeSeries_s.h"
#include <vector>
#include "Vector.h"

template <class T>
class CTimeSeriesSet
{
public:
	CTimeSeriesSet(void); //default constructor
	CTimeSeriesSet(int n); //construction with number of variables (timeseries)
	CTimeSeriesSet(int numberofBTCs, int sizeofBTCvector);
    CTimeSeriesSet(const CTimeSeriesSet<T> &BTC);
    CTimeSeriesSet(const CTimeSeries<T> &BTC);

	CTimeSeriesSet(std::string filename, bool varytime, uint64_t pos = 0,
        const std::vector<std::string>& names = {} /*unknown*/);

	void writetofile(char outputfile[]);
	int maxnumpoints();

	CTimeSeriesSet& operator = (const CTimeSeriesSet &C);

    bool writetofile(std::string outputfile, bool writeColumnHeaders = false, bool append = false);
	void writetofile(std::string outputfile, int writeinterval);

    std::vector<T> interpolate(T t);
    std::vector<T> interpolate(T t, int fnvars);

	void getfromfile(std::string filename, bool varytime);

    T maxtime();
    T mintime();

    std::vector<T> getrandom();
    std::vector<T> percentile(T x);
    std::vector<T> mean(int limit);
    std::vector<T> mean(int limit, std::vector<int> index);
    std::vector<T> std(int limit);
    std::vector<T> std(int limit, std::vector<int> index);

	CMatrix correlation(int limit, int n);
    std::vector<T> integrate();
    std::vector<T> average();
    std::vector<T> percentile(T x, int limit);
    std::vector<T> percentile(T x, int limit, std::vector<int> index);
    std::vector<T> getrandom(int burnin);

    void append(T t, std::vector<T> c);

    CTimeSeries<T> add(std::vector<int> ii);
    CTimeSeries<T> add_mult(std::vector<int> ii, std::vector<T> mult);
    CTimeSeries<T> add_mult(std::vector<int> ii, CTimeSeriesSet &mult);
    CTimeSeries<T> divide(int ii, int jj);
    CTimeSeriesSet make_uniform(T increment, bool assgn_d=true);
    CTimeSeriesSet getpercentiles(std::vector<T> percents);
    CVector out_of_limit(T limit);
	CTimeSeriesSet distribution(int n_bins, int n_columns, int limit);
    CTimeSeriesSet add_noise(std::vector<T> std, bool logd);

	void clear();

    std::vector<T> max_wiggle();
    std::vector<T> max_wiggle_corr(int _n = 10);
    std::vector<int> max_wiggle_sl(int ii, T tol);
    CTimeSeriesSet getflow (T A);

    void knockout(T t);
	int lookup(std::string S);
    std::vector<T> getrow(int a);
	void setname(int i, std::string name);
    void resize(unsigned int _size);
    void ResizeIfNeeded(unsigned int _increment);
    void adjust_size();
    bool file_not_found=false;

    CTimeSeries<T> &operator[](int index);
    CTimeSeries<T> &operator[](std::string BTCName);

    bool Contains(std::string BTCName);
#ifdef QT_version
	CTimeSeries &operator[](QString BTCName) {
		return operator[](BTCName.toStdString());}
#endif // QT_version

    CTimeSeriesSet(std::vector < std::vector<T>> &, int writeInterval = 1);
	int indexOf(const std::string& name) const;
	void pushBackName(std::string name);
    void append(const CTimeSeries<T> &BTC, std::string name = "");
	CTimeSeriesSet sort(int burnOut = 0);
#ifdef QT_version
	void compact(QDataStream &data) const;
	static CTimeSeriesSet unCompact(QDataStream &data);
#endif // QT_version
	~CTimeSeriesSet(void);

    int         nvars;
    std::string filename;
    std::vector<CTimeSeries<T>> BTC;
    std::vector<std::string> names;
    bool unif = false;

    uint64_t file_pos = 0llu;
};

template <class T> T diff(CTimeSeriesSet<T> B1, CTimeSeriesSet<T> B2);
template <class T> CTimeSeriesSet<T> operator * (const CTimeSeriesSet<T> &BTC, const double &C);
template <class T> CVector norm2dif(CTimeSeriesSet<T> &A, CTimeSeriesSet<T> &B);
template <class T> CTimeSeriesSet<T> merge(CTimeSeriesSet<T> A, const CTimeSeriesSet<T> &B);
template <class T> CTimeSeriesSet<T> merge(std::vector<CTimeSeriesSet<T>> &A);
template <class T> CVector sum_interpolate(std::vector<CTimeSeriesSet<T>> &BTC, double t);
template <class T> T sum_interpolate(std::vector<CTimeSeriesSet<T>> &BTC, T t, std::string name);
template <class T> int max_n_vars(std::vector<CTimeSeriesSet<T>> &BTC);

#include "TimeSeriesSet_s.hpp"
