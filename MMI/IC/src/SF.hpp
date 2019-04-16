#ifndef _SF_h_included_
#define _SF_h_included_

#define _USE_MATH_DEFINES
#include <cmath>
#include <numeric>
#include <iostream>
#include <vector>
#include <Eigen/Dense>
// #include <opencv2/opencv.hpp>
#include <string>
#include <fstream>

using namespace std;
using namespace Eigen;
// using namespace cv;

namespace IC { 

	/*
	Base functor for submodular function. Ground set V is {0 ... n-1} for some non-negative number n.
	*/
	class SF {
	public:
		/*
		The value of the submodular function evaluated on a set.
		@param B A subvector of elements of V.
		@return The value of the submodular function at B.
		*/
		virtual double operator() (const vector<size_t> &B) const = 0;
		/*
		@return The size of the ground set.
		*/
		virtual size_t size() const=0;
	};

	// class CartEntropy : public SF {
	// private:
	// 	vector<vector<double>> Genes; // genes matrix rows are condition, columns are genes
	// 	string Model;
	// public:
	// 	CartEntropy(vector<vector<double>> G, string model) {
	// 		Genes = G;
	// 		Model = model;
	// 	}

	// 	Ptr<ml::TrainData> get_dataset(const vector<size_t> &X, const size_t y) const
	// 	{
	// 		vector<vector<double>> genes;
	// 		for (auto& row : Genes) {               /* iterate over rows */
	// 			vector<double> temp;
	// 			for (auto &k : X)  {
	// 				temp.push_back(row[k]);
	// 			}
	// 			genes.push_back(temp);
	// 		}
			

	// 		vector<vector<double>> target;
	// 		for (auto& row : Genes) {               /* iterate over rows */
	// 			vector<double> temp{ row[y] }; 
	// 			target.push_back(temp);
	// 		}

	// 		cv::Mat labels = toMat(target);
	// 		cv::Mat mat = toMat(genes);

	// 		// cout << mat << endl;
	// 		// cout << labels << endl;
	// 		Ptr<ml::TrainData> data_set =
	// 			cv::ml::TrainData::create(mat, 
	// 			cv::ml::COL_SAMPLE,
	// 			labels
	// 			);

	// 		{
	// 			//vector<double> genes;
	// 			//for (auto& row : Genes) {               /* iterate over rows */
	// 			//	for (auto &k : X)  {
	// 			//		genes.push_back(row[k]);
	// 			//	}
	// 			//}
			

	// 			//vector<double> target;
	// 			//for (auto& row : Genes) {               /* iterate over rows */
	// 			//	target.push_back(row[y]);
	// 			//}

	// 			//cv::Mat labels = toRowMat(target);
	// 			//cv::Mat mat = toRowMat(genes);

	// 			//// cout << mat << endl;
	// 			//// cout << labels << endl;
	// 			//Ptr<ml::TrainData> data_set =
	// 			//	cv::ml::TrainData::create(mat, 
	// 			//	cv::ml::ROW_SAMPLE,
	// 			//	labels
	// 			//	);
	// 			//return data_set;
	// 		}

	// 		// cv::Mat labels = toMat(target);
	// 		// cv::Mat mat = toMat(genes);
	// 		// // cout << mat << endl;
	// 		// // cout << labels << endl;
	// 		// Ptr<ml::TrainData> data_set =
	// 		// 	cv::ml::TrainData::create(mat, 
	// 		// 	cv::ml::ROW_SAMPLE, 
	// 		// 	labels
	// 		// 	);
	// 		return data_set;
	// 	}

	// 	template<typename _Tp> static  cv::Mat toMat(const vector<vector<_Tp> > vecIn) {
	// 		cv::Mat_<_Tp> matOut(vecIn.size(), vecIn.at(0).size(), CV_32F);
	// 		for (int i = 0; i < matOut.rows; ++i) {
	// 			for (int j = 0; j < matOut.cols; ++j) {
	// 				matOut(i, j) = vecIn.at(i).at(j);
	// 			}
	// 		}
	// 		Mat formatted_matOut;
	// 		matOut.convertTo(formatted_matOut, CV_32F);
	// 		return formatted_matOut;
	// 	}

	// 	double variance (vector <double> v) const {
	// 		if (v.size() < 2)
	// 		{
	// 			return 0.0;
	// 		}
	// 		double sum = std::accumulate(std::begin(v), std::end(v), 0.0);
	// 		double mean =  sum / v.size();
		
	// 		double accum  = 0.0;
	// 		std::for_each (std::begin(v), std::end(v), [&](const double d) {
	// 			accum  += (d-mean)*(d-mean);
	// 		});

	// 		double var = accum/(v.size() - 1);
	// 		return var;
	// 	}

	// 	vector<double> get_column_vector (const size_t col) const{
	// 		vector<double> col_vector;
	// 		for (auto& row : Genes) {
	// 			col_vector.push_back(row[col]);
	// 		}
	// 		return col_vector;
	// 	}
		
	// 	double svr_mse (const Ptr<ml::TrainData> dataset) const {
	// 		int n_samples = dataset->getNSamples();
	// 		if (n_samples == 0) {
	// 			cerr << "No data";
	// 			exit(-1);
	// 		}
	// 		dataset->setTrainTestSplitRatio(0.90, false);
	// 		int n_train_samples = dataset->getNTrainSamples();
	// 		int n_test_samples = dataset->getNTestSamples();

	// 		cv::Ptr<cv::ml::SVM> svr = cv::ml::SVM::create();
	// 		svr->setKernel(cv::ml::SVM::KernelTypes::LINEAR);
	// 		svr->setType(cv::ml::SVM::Types::EPS_SVR);//For n-class classification problem with imperfect class separation
	// 		//svr->setC(5);
	// 		//svr->setP(0.01);
	// 		svr->setGamma(10.0);//for poly
	// 		svr->setDegree(0.1);//for poly
	// 		svr->setCoef0(0.0);//for poly
	// 		svr->setNu(0.1);
	// 		svr->setP(0.1);

	// 		// cout << "Training Support Vector Regressor..." << endl;
	// 		//svr->trainAuto(trainData);
	// 		svr->train(dataset);
	// 		bool trained = svr->isTrained();
	// 		if (!trained){
	// 			cout << "error occur during SVR training" << endl;
	// 		}
	// 		cv::Mat results;
	// 		float train_performance = svr->calcError(dataset,
	// 			true, // test error
	// 			results // cv::noArray()
	// 		);
	// 		return train_performance;
	// 	}

	// 	double mse (const Ptr<ml::TrainData> dataset) const {
	// 			// Thomas
	// 			// train the cart algorithm and return the mse loss

	// 		int n_samples = dataset->getNSamples();
	// 		if (n_samples == 0) {
	// 			cerr << "No data";
	// 			exit(-1);
	// 		}
	// 		// else {
	// 		// 	cout << "Read " << n_samples << " samples" << endl;
	// 		// }

	// 		// Split the data, so that 90% is train data
	// 		//
	// 		dataset->setTrainTestSplitRatio(0.90, false);
	// 		int n_train_samples = dataset->getNTrainSamples();
	// 		int n_test_samples = dataset->getNTestSamples();
	// 		// cout << "Found " << n_train_samples << " Train Samples, and "
	// 		// 	<< n_test_samples << " Test Samples" << endl;

	// 		// Create a DTrees
	// 		cv::Ptr<cv::ml::RTrees> dtree = cv::ml::RTrees::create();
			
	// 			// set parameters
	// 			float _priors[] = { 1.0, 10.0 };
	// 			cv::Mat priors(1, 2, CV_32F, _priors);
	// 			dtree->setMaxDepth(5);
	// 			dtree->setMinSampleCount(10);
	// 			dtree->setRegressionAccuracy(0.01f);
	// 			dtree->setUseSurrogates(false /* true */);
	// 			dtree->setMaxCategories(15);
	// 			dtree->setCVFolds(0 /*10*/); // nonzero causes core dump
	// 			dtree->setUse1SERule(true);
	// 			dtree->setTruncatePrunedTree(true);
	// 			dtree->setPriors( priors );
	// 			dtree->setPriors(cv::Mat()); // ignore priors for now...
			
	// 		// Now train the model
	// 		// NB: we are only using the "train" part of the data set
	// 		//
	// 		dtree->train(dataset);
	// 		// Having successfully trained the data, we should be able
	// 		// to calculate the error on both the training data, as well
	// 		// as the test data that we held out.
	// 		//
	// 		cv::Mat results;
	// 		float train_performance = dtree->calcError(dataset,
	// 			true, // test error
	// 			results // cv::noArray()
	// 		);

	// 		cv::Mat Test_results;
	// 		float test_performance = dtree->calcError(dataset,
	// 			false, // use train data
	// 			Test_results // cv::noArray()
	// 		);
	// 		return test_performance;
	// 	}

	// 	/*
	// 	Calculate the entropy of a gaussian subvector.
	// 	@param B subvector of elements from the ground set.
	// 	@return Entropy of the gaussian subvector indexed by elements in B.
	// 	*/
	// 	double operator() (const vector<size_t> &B) const 
	// 	{
	// 		// Handason
	// 		size_t n = B.size();
	// 		double h = 0;
	// 		// H(z1, z2, z3) = H(z1) + H(z2|z1) + H(z3|x1, x2)
	// 		for (size_t i = 0; i < n; i++)
	// 		{
	// 			if (i == 0)
	// 			{
	// 				// H(z0) = variance of gene 0
	// 				vector<double> genes_i = get_column_vector(B[i]);
	// 				h += variance(genes_i);  // variance of genes i
	// 			} 
	// 			else 
	// 			{
	// 				// H(z1|z0), H(z2|x0, x1), ...
	// 				// X = [0], y = 1, ..., X = [0, 1], y = 2, ...
	// 				vector<size_t> X(i);
	// 				// cout<<i<<endl;
	// 				for (size_t j = 0; j < i; j++){
	// 					// cout << "j: " << j << endl;
	// 					// cout<<B_[j]<<" ";
	// 					X[j] = B[j];
	// 				}
	// 				Ptr<ml::TrainData> temp_dataset = get_dataset(X, B[i]);
	// 				// cout << "mse: " << mse(temp_dataset) << endl;
	// 				if (Model == "cart"){
	// 					h += mse(temp_dataset);
	// 				} else if (Model == "svr"){
	// 					h += svr_mse(temp_dataset);
	// 				} else {
	// 					cout << "Model only support svr / cart" << endl;
	// 					cout << "Program Exit!";
	// 					exit(0);
	// 				}
	// 			}
	// 		}
			
	// 		// cout << "for B = {";
	// 		// for (auto i: B)
 	// 		// 	cout << i << ' ';
	// 		// cout << "}" << endl;

	// 		// cout << "cart entropy: " << h << "\n" << endl;
	// 		// // return 1;
	// 		return h;
	// 	}

	// 	size_t size() const {
	// 		// return Genes.cols();
	// 		return Genes[0].size();
	// 	}
	// };

	class TableEntropy : public SF {
	private:
		vector<double> EntropyTable;
		size_t num;

	public:
		TableEntropy(vector<double> E, size_t n){
			num = n;
			EntropyTable = E;
			if (n < 1)
			{
				throw runtime_error("wrong input!!");
			}
		}

		static vector<size_t> subsetVector(size_t size, size_t index)
		{
			vector<size_t> Output;
			//Get number of Element by order defined in 
			//CombinationIndex
			//use decomposition of combination
			//For example: r = 2, n = c + d, 2 <= min(c,d)
			//				nCr = (c + d)C2 = cC0*dC2 + cC1*dC1 + cC2*dC0
			//if index >= (order)C0, that means there are at least one element
			//in the vector
			size_t numOutput = 0, tempSum = 0;
			for (numOutput = 0; numOutput < size; numOutput++)
			{
				size_t comb = combination(size, numOutput);
				if (index >= tempSum + comb)
				{
					tempSum += comb;
				}
				else
				{
					break;
				}
			}
			if (numOutput >= size && (index > tempSum + combination(size, numOutput)))
			{
				cerr << "Unexpected result" << endl;
			}
			else
			{
				//Get Exact Elements
				//use decomposition of combination by order defined in 
				//CombinationIndex
				//i.e. 4C2 = 1C0*3C2 + 1C1*3C1
				//First find exactance of most weighted element (3 in ab. ex)
				//if (index - tempSum) >= 3C2, that means 3 is in the vector
				int element;
				for (element = size - 1; element >= 0; element--)
				{
					if (index - tempSum == 0)
					{
						//Fill in remaining with the smallest elements
						for (size_t i = 0; i < numOutput; i++)
						{ 
							Output.push_back(i);
						}
						break;
					}
					else if (element >= numOutput)
					{
						if (0 == numOutput)
						{
							break;
						}
						if ((index - tempSum) >= combination(element, numOutput))
						{
							tempSum += combination(element, numOutput);
							Output.push_back(element);
							numOutput--;
						}
					}
					else
					{
						cerr << "Unexpected result" << endl;
						break;
					}
				}
			}
			return Output;
		}

		static size_t combination(size_t n, size_t r)
		{
			if (r > n)
			{
				return 0;
			}
			size_t numerator = 1, denomiator = 1;
			for (size_t i = 0; i < r; i++)
			{
				denomiator *= (i + 1);
				numerator *= n - i;
			}
			return numerator / denomiator;
		}

		//CombinationIndex iterator element in combination increasing order
		//zero-based comb 
		//size is number of element in universe
		//for example
		//	Index	|Elements (order = 4)
		//	0		|0000
		//	1		|0001
		//	2		|0010
		//	3		|0100
		//	4		|1000
		//	5		|0011
		//	6		|0101
		//	7		|0110
		//	8		|1001
		//	9		|1010
		//	10		|1100
		//	11		|0111
		//	12		|1011
		//	13		|1101
		//	14		|1110
		//	15		|1111
		static size_t subsetIndex(size_t size, vector<size_t> comb)//, bool verbose = false)
		{
			// if (verbose)
			// {
			// 	cout << "Find index of {";
			// 	for (int i = comb.size() - 1; i >= 0; i--)
			// 	{
			// 		cout << comb[i] << ", ";
			// 	}
			// 	cout << "} in a set with size = " << size << endl;
			// }

			size_t index = 0;
			size_t condSize = comb.size();
			sort(comb.begin(), comb.end());
			// if (verbose)
			// {
			// 	cout << "it is ";
			// }
			//for (int i = condSize - 1; i >= 0; i--)
			for (int i = 0; i < condSize; i++)
			{
				index += combination(size, i);
				// if (verbose)
				// {
				// 	cout << size << "C" << i << "  ";
				// }
			}
			size_t prev = 0;
			size_t subsetSize = condSize;
			int  i = comb.size() - 1;
			for (int i = condSize - 1; i >= 0; i--)
			{
				if (comb[i] > i)
				{
					index += combination(comb[i], i + 1);
					// if (verbose)
					// {
					// 	cout << comb[i] << "C" << i + 1 << "  ";
					// }
				}
			}
			// if (verbose)
			// {
			// 	cout << endl;
			// 	cout << index << endl;
			// }
			return index;
		}

		double operator() (const vector<size_t> &B) const {
			vector<size_t> B_ = B;
			return EntropyTable[subsetIndex(num, B_)];
		}

		size_t size() const {
			return num;
		}
    };


	class GaussianEntropy : public SF {
	private:
		MatrixXd Sigma; // covariance matrix

	public:
		/*
		Construct a submodular function as the entropy function of a gaussian random vector with specified covariance matrix.
		@param S Covariance matrix.
		*/
		GaussianEntropy(MatrixXd S) {
			Sigma = S;
			if (Sigma.rows() != Sigma.cols())
				throw std::runtime_error("S must be an SPD matrix.");
		}
		/*
		Calculate the entropy of a gaussian vector with a given covariance matrix.
		@param S Covariance matrix.
		@return differential entropy of the gaussian vector with covariance matrix S.
		*/
		static double h(const MatrixXd &S) {
			const double c = log(2 * M_PI*M_E) / 2;
			LLT<MatrixXd> lltOfS(S);
			if (lltOfS.info() == Eigen::NumericalIssue)
			{
				cout << "S submatrix " << endl << S << endl;
				throw std::runtime_error("S must be an SPD matrix.");
			}
			size_t k = S.rows();
			double det = c*k;
			MatrixXd L = lltOfS.matrixL();
			for (size_t i = 0; i < k; i++) {
				det += log(L(i, i));
			}
			return det;
		}

		/*
		Calculate the entropy of a gaussian subvector.
		@param B subvector of elements from the ground set.
		@return Entropy of the gaussian subvector indexed by elements in B.
		*/
		double operator() (const vector<size_t> &B) const {
			size_t n = B.size();
			MatrixXd S(n, n);
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++) {
					S(i, j) = Sigma(B[i], B[j]);
				}
			}
			return h(S);
		}

		size_t size() const {
			return Sigma.rows();
		}
	};

	/*
	Find the point in the base polytope of the normalized version of a submodular function
	that minimizes the weighted sum of coordinates.
	@param f The submodular function
	@param w The weight vector with length equal to that of the ground set of f.
	@return The vector x in B(f-f(emptySet)) such w'x is minimized.
	*/
	VectorXd edmonds_greedy(const SF &f, const VectorXd &w) {
		size_t n = f.size();
		if (n != w.size())
			throw runtime_error("w must have the same size as the ground set of f.");
		vector<size_t> idx(n);
		VectorXd x(n);
		iota(idx.begin(), idx.end(), 0);
		sort(idx.begin(), idx.end(), [&](size_t i1, size_t i2) {return w[i1] < w[i2]; });
		vector<size_t> B;
		double F = f(B);
		for (auto i : idx) {
			x[i] = -F;
			B.push_back(i);
			F = f(B);
			x[i] += F;
		}
		return x;
	}

	/*
	Compute the minimum norm base in the base polytope of the normalized version of a submodular function
	with specified tolerance and precision. N.b., set function tolerance to 1E-6 or above due to the numerical issue with Eigen.
	@param f The submodular function
	@param fn_tol Function Tolerance
	@param eps Precision
	@return The minimum norm point of the base B(f-f(emptySet)).
	*/
	VectorXd min_norm_base(const SF &f, double fn_tol, double eps) {
		size_t n = f.size();
		VectorXd x;
		if (n < 1)
			return x;
		x = VectorXd::Ones(n);
		if (n == 1) {
			vector<size_t> V(n);
			iota(V.begin(), V.end(), 0);
			return x*f(V);
		}
		// Step 0 (Initialize a trivial corral Q and x=Nr Q)
		x = edmonds_greedy(f, x);
		//cout << f(vector<size_t> {0, 1}) - f(vector<size_t> {0}) << endl;
		//cout << x.transpose() << endl;
		MatrixXd Q(n, n + 1);
		Q.col(0) = x;
		size_t numCorral = 1; // Corral: First numCorral columns of Q

		VectorXd w = VectorXd::Zero(n + 1);
		w(0) = 1; // maintain x == Q * w

				// initialization for adaptive computation of the projection to affine hull of the corral
		VectorXd e = VectorXd::Ones(n + 1);
		MatrixXd L = MatrixXd::Zero(n + 1, n + 1);
		L(0, 0) = sqrt(1 + x.dot(x));	// maintain L*L.transpose() == e*e.transpose() + Q.transpose() * Q
										// for the first numCorral rows and columns.
		double old_first_order_opt,first_order_opt = INFINITY;
		size_t stuck_count;
		while (1) {
			// Step 1 (Major cycle: move towards origin along the direction of x)
			VectorXd q = edmonds_greedy(f, x);
			old_first_order_opt = first_order_opt;
			first_order_opt = abs(x.dot(q) - x.dot(x));
			//log<LOG_INFO>(L"[min_norm_base] First order optimality : %1% ") % first_order_opt;
			// stopping criteria
			if (first_order_opt < fn_tol) { 
				return x; // x separates the base polytope from the origin and is therefore the minimum norm point.
			}
			if (old_first_order_opt <= first_order_opt) { // stuck
				stuck_count++;
				cout << "stuck : " << stuck_count << " " << first_order_opt << endl;
				if (stuck_count > 100) { // avoid getting stuck for too long
					cout << "Unstuck at gap to optimality: " << first_order_opt << endl;
					return x;
				}
			}
			else {
				stuck_count = 0;
			}
			{
				// Step 2 (Major cycle: project to affine hull)
				auto L_ = L.topLeftCorner(numCorral, numCorral).triangularView<Lower>();
				auto Q_ = Q.topLeftCorner(n, numCorral);
				auto e_ = e.topRows(numCorral);
				VectorXd r = L_.solve(e_ + Q_.transpose() * q);
				L.block(numCorral, 0, 1, numCorral) = r.transpose();
				L(numCorral, numCorral) = 1 + q.dot(q) - r.dot(r);
				//cout << "Optimality test:" << endl;
				//cout << "x : " << x.transpose() << endl;
				//cout << "q : " << q.transpose() << endl;
				//cout << "Q : " << endl << Q_ << endl;
				if (1 + q.dot(q) - r.dot(r) < 0) {
					//cout << "Update L to include q:" << endl;
					//cout << "L: " << endl << (MatrixXd) L_ << endl;
					//cout << "r: " << r.transpose() << endl;
					throw runtime_error("Try to set a higher functional tolerance.");
				}
				L(numCorral, numCorral) = sqrt(1 + q.dot(q) - r.dot(r));
				Q.col(numCorral++) = q;
			}
			int minor_cycle_count = 0; // count number of iterations of minor cycles in iteration of the major cycle 
			while (1) {
				minor_cycle_count = minor_cycle_count + 1;
				auto L_ = L.topLeftCorner(numCorral, numCorral).triangularView<Lower>();
				auto Q_ = Q.topLeftCorner(n, numCorral);
				auto e_ = e.topRows(numCorral);
				VectorXd v = L_.transpose().solve(L_.solve(e_));
				v = (e_ * e_.transpose() + Q_.transpose() * Q_).llt().solve(e_); // cc
				v = v / e_.dot(v);
				//cout << "Affine projection: origin onto aff(Q) " << endl;
				//cout << "L : " << endl << (MatrixXd)L_ << endl;
				//cout << "Q : " << endl << Q_ << endl;
				//cout << "v : " << v.transpose() << endl;
				bool minor_cycle = false;
				{
					size_t i = 0;
					while (!minor_cycle && i < numCorral)
						minor_cycle = (v(i++) <= eps);
				}
				auto w_ = w.topRows(numCorral);
				if (!minor_cycle) {
					// continue with Main Cycle
					w_ = v;
					x = Q_*w_;
					//log<LOG_INFO>(L"[min_norm_base] # minor cycles : %1% ") % minor_cycle_count;
					break;
				}
				// Step 3: Minor cycle
				double theta = 1;
				for (size_t i = 0; i < numCorral; i++) {
					if (w_(i) - v(i)>= eps) {
						theta = min(theta, w_(i) / (w_(i) - v(i)));
					}
				}
				w_ = (1 - theta) * w_ + theta *v;
				size_t i_ = 0;
				vector<bool> toDelete(numCorral);
				for (size_t i = 0; i < numCorral; i++) {
					if ((toDelete[i] = (w_(i) <= eps))) {
						for (size_t j = i; j < numCorral - 1; j++) {
							// Maintain L triangular after deletion
							double a = L(j + 1, j), b = L(j + 1, j + 1);
							double c = sqrt(a*a + b*b);
							Matrix2d T;
							T << a / c, -b / c, b / c, a / c;
							L.block(j + 1, j, numCorral - j, 2) *= T;
						}
					}
				}
				// perform deletion
				for (size_t i = 0; i < numCorral; i++) {
					if (!toDelete[i]) {
						if (i_<i) {
							w_(i_) = w_(i);
							Q.col(i_) = Q.col(i);
							L.row(i_) = L.row(i);
						} // else, i.e., i_=i : no need to move
						i_++;
					} // else: delete ith corral
				}
				numCorral = i_;
				x = Q.topLeftCorner(n, numCorral)*w.topRows(numCorral);
			}
		}
		return x;
	}
		
	/*
	Compute the minimum norm base in the base polytope of the normalized version of a submodular function with
	the function tolerance 1E-10, optimality tolerance 1E-10 and precision epsilon 1E-15.
	@param f The submodular function
	@return The minimum norm point of the base B(f-f(emptySet)).
	*/
	VectorXd min_norm_base(const SF &f) {
		return min_norm_base(f, 1E-10, 1E-15);
	}


	class DataPreprocessing {
	public:
		virtual bool loadFile(string filename, size_t mode = 0) = 0;
		virtual bool fillMissingData(size_t mode = 0) = 0;
		virtual bool normalize(size_t mode = 0) = 0;
		virtual bool quantize(size_t mode = 0) = 0;
	};

	class CSV : public DataPreprocessing {
	public:
		typedef enum ENUM_CSV_MODE {
			CSV_DEFAULT = 0x0,
			CSV_VERBOSE = 0x1
		}CSV_MODE;

		vector<vector<double>> data;

		vector<size_t> MissingDataRow;
		vector<size_t> MissingDataCol;

		bool loadFile(string filename, size_t mode) {
			ifstream f;
			f.open(filename.c_str());
			if (!f.is_open())
			{
				std::cerr << "error: file open failed '" << filename << "'.\n";
				return false;
			}
			string line, val;
			size_t j = 0;
			while (std::getline(f, line)) {        /* read each line */
				std::vector<double> v;                 /* row vector v */
				std::stringstream s(line);         /* stringstream line */
				size_t i = 0;
				while (getline(s, val, ','))       /* get each value (',' delimited) */
				{
					double value = 0.0;
					char *endptr = 0; 
					value = strtod(val.c_str(), &endptr);
					if (*endptr != '\0' || endptr == val.c_str()) {
						value = 0.0;
						MissingDataRow.push_back(i);
						MissingDataRow.push_back(j);
					}
					v.push_back(value);  /* add to row vector */
					i++;
				}
				data.push_back(v);                /* add row vector to array */
				j++;
			}
			if (CSV_VERBOSE & mode) {
				for (auto& row : data) {               /* iterate over rows */
					for (auto& val : row)               /* iterate over vals */
						std::cout << val << "  ";       /* output value      */
					std::cout << "\n";                  /* tidy up with '\n' */
				}
			}
			return true;
		}
		bool fillMissingData(size_t mode) {
			return true;
		}
		bool normalize(size_t mode) {
			return true;
		}
		bool quantize(size_t mode) {
			return true;
		}
	};
}
#endif