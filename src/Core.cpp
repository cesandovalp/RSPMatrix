#include "MatrixFactory.hpp"
#include <Rcpp.h>
using namespace Rcpp;

void FillMatrix( sp::Matrix<double>* M )
{
  for( unsigned i = 0; i < M->rows; ++i )
    for( unsigned j = 0; j < M->columns; ++j )
      M->data[i * M->columns + j] = i * M->columns + j;
}

// [[Rcpp::export]]
List rcpp_hello_world( )
{
    CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;
    
    sp::MatrixFactory::instance()->SetMode( sp::sequential );

    return z ;
}

// [[Rcpp::export]]
void SetSequential( )
{
  sp::MatrixFactory::instance()->SetMode( sp::sequential );
}

// [[Rcpp::export]]
void SetMulticore( )
{
  sp::MatrixFactory::instance()->SetMode( sp::multicore );
}

// [[Rcpp::export]]
void SetGPU( )
{
  sp::MatrixFactory::instance()->SetMode( sp::gpu );
}

// [[Rcpp::export]]
SEXP SPMatrix( double rows, double columns )
{
  auto result = sp::MatrixFactory::instance()->CreateMatrixPtr<double>( rows, columns );
  return XPtr<sp::Matrix<double>>( result );
}

// [[Rcpp::export]]
void FillSPMatrix( SEXP m )
{
  auto m_ = XPtr<sp::Matrix<double>>( m );
  FillMatrix( m_ );
}

// [[Rcpp::export]]
void SPMultiplication( SEXP a, SEXP b )
{
  auto a_ = XPtr<sp::Matrix<double>>( a );
  auto b_ = XPtr<sp::Matrix<double>>( b );
  
  (*a_) *= (*b_);
}

// [[Rcpp::export]]
void SPAddition( SEXP a, SEXP b )
{
  auto a_ = XPtr<sp::Matrix<double>>( a );
  auto b_ = XPtr<sp::Matrix<double>>( b );
  
  (*a_) += (*b_);
}

// [[Rcpp::export]]
void PrintSPMatrix( SEXP m )
{
  auto m_ = XPtr<sp::Matrix<double>>( m );

  for( unsigned i = 0; i < m_->rows; ++i )
  {
    for( unsigned j = 0; j < m_->columns; ++j )
      Rcout << m_->data[i * m_->columns + j] << "\t|";
    Rcout << std::endl;
  }
}
