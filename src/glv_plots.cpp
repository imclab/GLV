/*	Graphics Library of Views (GLV) - GUI Building Toolkit
	See COPYRIGHT file for authors and license information */

#include <float.h>
#include "glv_util.h"
#include "glv_plots.h"

namespace glv{

/*
Requirements:
Multiple graphs viewable within same plotting region.
Support for different plotting styles- line, bar, scatter, polar
Support for 1D and 2D plots

J
	basic plot types:
	surface/wire, line, symbol/dot
	
	array is set of points where dim=0 dependent, dim>0 independent

Dimension=0 compact dimension
Dimension>0 dimension of embedding space

Shape
(1, Nx,  1, 1)	1D curve (dependent x, independent y)
(1,  1, Ny, 1)	1D curve (dependent y, independent x)
(2, Nx,  1, 1)	2D curve
(2,  1, Ny, 1)	2D curve
(3, Nx,  1, 1)	3D curve

(1, Nx, Ny, 1)	2D density or 3D surface
(2, Nx, Ny, 1)	2D density colored
(3, Nx, Ny, 1)	2D density colored

All plotters present multidimensional arrays in a consistent way. Dimensions
are treated as follows:

0: inner dimensions (i.e., color, position, glyph shape)
1: x dimensions
2: y dimensions
3: z dimensions

Type		Shape			Memory
1D x		(1, n, 1)		(x1, x2, x3)
1D y		(1, 1, n)		((y1, y2, y3))
2D Scatter	(2, n)			((x1, y1), (x2, y2), (x3, y3))				
3D Scatter	(3, n)			((x1, y1, z1), (x2, y2, z2), (x3, y3, z3))
xy			(n, 2)			((x1, x2, x3), (y1, y2, y3))
xyz			(n, 3)			((x1, x2, x3), (y1, y2, y3), (z1, z2, z3))

Density		(C, n, m)		((v11, v21, v31), (v12, v22, v32))
Surface z	(1, n, m, 1)	((v11, v21, v31), (v12, v22, v32))
Surface y	(1, n, 1, m)	((v11, v21, v31), (v12, v22, v32))
Surface x	(1, 1, n, m)	((v11, v21, v31), (v12, v22, v32))

*/


PlotDensity::PlotDensity(const Color& c)
:	Plottable(draw::Triangles, 1, c), mTex(0,0, GL_RGB, GL_FLOAT), mIpol(0)
{
}

void PlotDensity::onContextCreate(){
	// note: texture created in onPlot since we don't know the size
	//mTex.create();
}

void PlotDensity::onContextDestroy(){
	mTex.destroy();
	mTex.dealloc();
}

// polar coloring
//			float w0 = d.at<float>(0,i[0],i[1],i[2]);
//			float w1 = d.at<float>(1,i[0],i[1],i[2]);
//			
//			double m = hypot(w0,w1);
//			double a = atan2(w1,w0)/(-2*M_PI); if(a<0) a=1+a;
//			Color c = HSV(a, 1, m);

void PlotDensity::onPlot(draw::GraphicsData& b, const Data& d, const Indexer& i){
//	double dx = 2./d.size(1);
//	double dy = 2./d.size(2);
	
	int N0 = d.size(0);	// number of "internal" dimensions
	HSV hsv = mColor;

	int Nbytes = mTex.alloc(d.size(1), d.size(2));
	if(Nbytes){
		mTex.create(); //printf("tex %d: %d bytes\n", mTex.id(), Nbytes);
	}

	switch(N0){
	case 1:
		while(i()){
			float w0 = d.at<float>(0,i[0],i[1],i[2]);
			Color c = mColor * w0;
			float * tbuf = mTex.buffer<float>();
			int ind = i.indexFlat(0,1);
			tbuf[ind*3+0] = c.r;
			tbuf[ind*3+1] = c.g;
			tbuf[ind*3+2] = c.b;

//			the non-texture approach...
//			double x = i.frac(0)*2 - 1;
//			double y = i.frac(1)*2 - 1;
//			float w0 = d.at<float>(0,i[0],i[1],i[2]);
//			Color c = mColor * w0;
//			int idx = b.vertices2().size();
//			b.addVertex2(x,y, x+dx,y, x+dx,y+dy, x,y+dy);
//			b.addColor(c,c,c,c);
//			b.addIndex(idx+0, idx+1, idx+3);
//			b.addIndex(idx+1, idx+2, idx+3);
		}
		break;

	case 2:
		while(i()){
			float w0 = d.at<float>(0,i[0],i[1],i[2]);
			float w1 = d.at<float>(1,i[0],i[1],i[2]);
			Color c = HSV(hsv.h, hsv.s*w1, hsv.v*w0);
			float * tbuf = mTex.buffer<float>();
			int ind = i.indexFlat(0,1);
			tbuf[ind*3+0] = c.r;
			tbuf[ind*3+1] = c.g;
			tbuf[ind*3+2] = c.b;
		}
		break;

	case 3:
	case 4:
		while(i()){
			float w0 = d.at<float>(0,i[0],i[1],i[2]);
			float w1 = d.at<float>(1,i[0],i[1],i[2]);
			float w2 = d.at<float>(2,i[0],i[1],i[2]);
			Color c = Color(w0, w1, w2);
			float * tbuf = mTex.buffer<float>();
			int ind = i.indexFlat(0,1);
			tbuf[ind*3+0] = c.r;
			tbuf[ind*3+1] = c.g;
			tbuf[ind*3+2] = c.b;
		}
		break;

	default:;
	}

	mTex.magFilter(mIpol ? GL_LINEAR : GL_NEAREST);
	draw::enable(draw::Texture2D);
	draw::color(1,1,1,1);
	mTex.begin();
	mTex.send();
	mTex.draw(-1,1,1,-1);
	mTex.end();
	draw::disable(draw::Texture2D);
}


void PlotFunction1D::onPlot(draw::GraphicsData& g, const Data& d, const Indexer& i){
//	Indexer j(i.size());
//	while(j()){
//		double x = j[0];
//		double y = d.at<double>(0, j[0]);
//		g.addVertex(x, y);
//	}

	/*
	dim		mapping
	0		position
	1		number of points along x
	2		number of points along y
	*/

	//int N0 = d.size(0);
	int N1 = d.size(1);
	int N2 = d.size(2);

	if(N2==1){
		while(i()){
			double x = i[0];
			double y = d.at<double>(0, i[0]);
			g.addVertex(x, y);
		}
	}
	else if(N1==1){
		while(i()){
			double x = d.at<double>(0, 0, i[1]);
			double y = i[1];
			g.addVertex(x, y);
		}	
	}
}


void PlotFunction2D::onPlot(draw::GraphicsData& g, const Data& d, const Indexer& i){
	if(d.size(0) < 2) return;
	while(i()){
		double x = d.at<double>(0, i[0], i[1]);
		double y = d.at<double>(1, i[0], i[1]);
		g.addVertex(x, y);
	}
}



Plot::Plot(const Rect& r)
:	Grid(r)
{	resetValInd();
}

Plot::Plot(const Rect& r, Plottable& p)
:	Grid(r)
{	resetValInd();
	add(p);
}

void Plot::onDraw(GLV& g){
	Grid::onDraw(g);
	draw::GraphicsData& gd = g.graphicsData();
	draw::color(colors().fore);

	// push into grid space and call attached plottables
	pushGrid();
		Plottables::iterator i = mPlottables.begin();
		while(i != mPlottables.end()){
			gd.reset();
			Plottable& p = **i;
			p.doPlot(gd, p.data().hasData() ? p.data() : data());
			++i;
		}
	popGrid();
}

bool Plot::onEvent(Event::t e, GLV& g){
	Grid::onEvent(e,g);
	switch(e){
	case Event::WindowCreate:
	{	Plottables::iterator i = mPlottables.begin();
		while(i != mPlottables.end()){ (**i).onContextCreate(); ++i; } }
		break;
	case Event::Quit:
	case Event::WindowDestroy:
	{	Plottables::iterator i = mPlottables.begin();
		while(i != mPlottables.end()){ (**i).onContextDestroy(); ++i; } }
		break;
	default:;
	}
	return true;
}

Plot& Plot::add(Plottable& v){ mPlottables.push_back(&v); return *this; }

Plot& Plot::remove(Plottable& v){
	std::remove(mPlottables.begin(), mPlottables.end(), &v);
	return *this;
}

//
///// Density plot
//
///// Model data should have a shape of (nc, nx, ny) where 'nc' si the number of
///// components of the value (e.g., a scalar is 1) and 'nx' and 'ny' are the size
///// of the x and y dimensions, respectively.
//class DensityPlot : public Plot {
//public:
//	DensityPlot(const Rect& r=Rect());
//
//	DensityPlot& color(const Color& v){ mColor1=v; return *this; }
//
//	virtual const char * className() const { return "DensityPlot"; }
//	virtual void onDraw(GLV& g);
//
//protected:
//	Color mColor1;
////	float val(int i, int j, int k){ return to01(data().at<float>(i,j,k)); }
//	float val(int i, int j, int k){ return (data().at<float>(i,j,k)); }
//};


//DensityPlot::DensityPlot(const Rect& r)
//:	Plot(r)
//{
//	data().type(Data::DOUBLE);
//}
//
//void DensityPlot::onDraw(GLV& g){
//	using namespace glv::draw;
//	if(data().size() == 0) return;
//
//	float xd = dx(1);
//	float yd = dy(2);
//	int N0 = data().size(0);
//	int N1 = data().size(1);
//	int N2 = data().size(2);
////	int order = model().order();
//	HSV hsv = mColor1;
//
///*
//  .   .   .
//1        
//  .   .   .
//0        
//  .   .   .
//    0   1
//
//prim			Nv	Ni
//Quads			4N	4N
//Triangles		4N	6N
//TriangleStrip	4N	6N
//*/
//
////	int Np = (N1+1)*(N2+1);
////	Color cols[Np];
////	Point2 pts[Np];
////	unsigned inds[N1*2*N2 + 2*N2];
////	int ii=-1;
////	int iv=0;
////
////	glShadeModel(GL_FLAT);
////
////	for(int j=0; j<N2+1; ++j){
////		for(int i=0; i<N1+1; ++i){
////			float x = xd*i;
////			float y = yd*j;
////			int i1 = i!=N1 ? i : i-1;
////			int i2 = j!=N2 ? j : j-1;
////
////			Color c;
////			switch(N0){
////			case 1: c = HSV(hsv.h, hsv.s, hsv.v*val(0,i1,i2)); break;
////			case 2: c = HSV(hsv.h, hsv.s*val(1,i1,i2), hsv.v*val(0,i1,i2)); break;
////			case 3:	c = Color(val(0,i1,i2), val(1,i1,i2), val(2,i1,i2), 1); break;
////			default:c = Color(val(0,i1,i2), val(1,i1,i2), val(2,i1,i2), val(3,i1,i2));
////			}
////			
////			cols[iv] = c;
////			pts[iv](x,y);
////			++iv;
////			
////			if(j < N2){
////				inds[++ii] = (j  )*(N1+1) + i;
////				inds[++ii] = (j+1)*(N1+1) + i;
////				
////				if(i == N1){
////					inds[ii+1] = inds[ii]; ++ii;
////					inds[++ii] = (j+1)*(N1+1);
////				}
////			}
////		}
////	}
////
////	draw::paint(draw::TriangleStrip, pts, cols, inds, ii);
////
////	glShadeModel(GL_SMOOTH);
//
//#ifdef GLV_USE_OPENGL_ES
//	GraphicsData& b = g.graphicBuffers();
//	b.reset();
//
//	for(int j=0; j<N2; ++j){
//		float y = yd*j;
//		for(int i=0; i<N1; ++i){
//			float x = xd*i;
//
//			Color c;
//			switch(N0){
//			case 1: c = HSV(hsv.h, hsv.s, hsv.v*val(0,i,j)); break;
//			case 2: c = HSV(hsv.h, hsv.s*val(1,i,j), hsv.v*val(0,i,j)); break;
//			case 3:	c = Color(val(0,i,j), val(1,i,j), val(2,i,j), 1); break;
//			default:c = Color(val(0,i,j), val(1,i,j), val(2,i,j), val(3,i,j));
//			}
//			
//			int ind = b.vertices2().size();
//			b.addColor(c,c,c,c);			
//			b.addVertex2(x,y, x+xd,y, x+xd,y+yd, x,y+yd);
//			b.addIndex(ind+0, ind+1, ind+3);
//			b.addIndex(ind+1, ind+2, ind+3);
//		}
//	}
//	
//	paint(Triangles, b);
//#else
//	GraphicsData& b = g.graphicsData();
//	b.reset();
//
//	for(int j=0; j<N2; ++j){
//		float y = yd*j;
//		for(int i=0; i<N1; ++i){
//			float x = xd*i;
//
//			Color c;
//			switch(N0){
//			case 1: c = HSV(hsv.h, hsv.s, hsv.v*val(0,i,j)); break;
//			case 2: c = HSV(hsv.h, hsv.s*val(1,i,j), hsv.v*val(0,i,j)); break;
//			case 3:	c = Color(val(0,i,j), val(1,i,j), val(2,i,j), 1); break;
//			default:c = Color(val(0,i,j), val(1,i,j), val(2,i,j), val(3,i,j));
//			}
//			
//			b.addColor(c,c,c,c);			
//			b.addVertex2(x,y, x+xd,y, x+xd,y+yd, x,y+yd);
//		}
//	}
//	paint(Quads, b);
//#endif
//}


} // glv::
