#ifndef INC_GLV_PLOTS_H
#define INC_GLV_PLOTS_H

/*	Graphics Library of Views (GLV) - GUI Building Toolkit
	See COPYRIGHT file for authors and license information */

#include <algorithm>
#include <vector>
#include <set>
#include "glv_core.h"
#include "glv_draw.h"
#include "glv_grid.h"
#include "glv_texture.h"
#include "glv_widget.h"

namespace glv{

class Plot;
class Plottable;



/// Map from model data to graphics data
class GraphicsMap{
public:
	virtual ~GraphicsMap(){}
	
	/// Routine to generate graphics from model data
	virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind) = 0;
};



/// Defines a routine for generating plot graphics from model data
class Plottable : public GraphicsMap{
public:

	enum BlendMode {
		TRANSPARENT = 0,
		ADDITIVE,
		SUBTRACTIVE
	};


	/// @param[in] prim		drawing primitive
	/// @param[in] stroke	width of lines or points
	Plottable(int prim=draw::Points, float stroke=1)
	:	mPrim(prim), mStroke(stroke), mBlendMode(TRANSPARENT), mLineStipple(-1),
		mDrawUnder(false), mUseStyleColor(true)
	{}

	/// @param[in] prim		drawing primitive
	/// @param[in] stroke	width of lines or points
	/// @param[in] col		color
	Plottable(int prim, float stroke, const Color& col)
	:	mPrim(prim), mStroke(stroke), mBlendMode(TRANSPARENT), mLineStipple(-1),
		mDrawUnder(false)
	{
		color(col);
	}

	virtual ~Plottable(){}

	/// Called when a new graphics context is created
	virtual void onContextCreate(){}
	
	/// Called when the current graphics context is destroyed
	virtual void onContextDestroy(){}

	virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind){}


	/// Set blend mode
	Plottable& blendMode(BlendMode v){ mBlendMode=v; return *this; }

	/// Get blend mode
	BlendMode blendMode() const { return mBlendMode; }

	/// Get color
	const Color& color() const { return mUseStyleColor ? Style::standard().color.fore : mColor; }
	Plottable& color(const Color& v){ mUseStyleColor=false; mColor=v; return *this; }
	
	Plottable& useStyleColor(bool v){ mUseStyleColor=v; return *this; }

	/// Get data
	const Data& data() const { return mData; }
	Data& data(){ return mData; }
	
	bool drawUnderGrid() const { return mDrawUnder; }
	Plottable& drawUnderGrid(bool v){ mDrawUnder=v; return *this; }
	
	/// Get line stippling pattern
	short lineStipple() const { return mLineStipple; }
	
	/// Set line stippling pattern
	Plottable& lineStipple(short v){ mLineStipple=v; return *this; }	
	
	/// Get geometric primitive
	int prim() const { return mPrim; }	

	/// Set geometric primitive
	Plottable& prim(int v){ mPrim=v; return *this; }

	/// Get line stroke width (for lines and points)
	float stroke() const { return mStroke; }	

	/// Set line stroke width (for lines and points)
	Plottable& stroke(float v){ mStroke=v; return *this; }

	/// Add a graphics map
	Plottable& add(GraphicsMap& v);

	/// Remove a graphics map
	Plottable& remove(GraphicsMap& v);

protected:
	friend class Plot;

	typedef std::vector<GraphicsMap *> GraphicsMaps;

	int mPrim;
	float mStroke;
	BlendMode mBlendMode;
	Color mColor;
	Data mData;
	GraphicsMaps mGraphicsMaps;
	short mLineStipple;
	bool mDrawUnder;
	bool mUseStyleColor;
	
	void doPlot(GraphicsData& gd, const Data& d);
	
	// defines how graphics data should be drawn
	virtual void onDraw(GraphicsData& gd, const Data& d){
		draw::paint(prim(), gd);
	}
};




/// Density plotter
class PlotDensity : public Plottable{
public:

	/// @param[in] color		plot color
	/// @param[in] hueSpread	amount spread hue for positive and negative values
	/// @param[in] interpolate	interpolation (0=none, 1=linear)
	PlotDensity(const Color& color=Color(1,0,0), float hueSpread=0, int interpolate=0);

	PlotDensity& hueSpread(float v){ mHueSpread=v; return *this; }

	/// Set interpolation mode (0=none, 1=linear)
	PlotDensity& interpolate(int v){ mIpol=v; return *this; }

	/// Set rectangular plotting region
	PlotDensity& plotRegion(const Interval<double>& vx, const Interval<double>& vy){
		mRegion[0] = vx; mRegion[1] = vy; return *this;
	}

//	static GraphicsMap& defaultColorMap();
//
//	struct DefaultColorMap : public GraphicsMap{
//		virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind);
//	};

	virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind);

protected:
	virtual void onContextCreate();
	virtual void onContextDestroy();
	virtual void onDraw(GraphicsData& gd, const Data& d);
	Texture2 mTex;
	Interval<double> mRegion[2];
	float mHueSpread;
	int mIpol;
};


/// One-dimensional function plotter
class PlotFunction1D : public Plottable{
public:

	enum PathStyle{
		DIRECT,			/**< Function values are vertices */
		ZIGZAG,			/**< Zig-zag between domain axis and function values */
//		SPIKE,
//		STEP
	};


	/// @param[in] color	plot color
	/// @param[in] stroke	stroke width
	/// @param[in] prim		drawing primitive
	/// @param[in] path		path style
	PlotFunction1D(
		const Color& color = Color(0),
		float stroke = 1,
		int prim = draw::LineStrip,
		PathStyle path = DIRECT
	);

	PlotFunction1D& pathStyle(PathStyle v){ mPathStyle=v; return *this; }

	virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind);

//	static GraphicsMap& defaultVertexMap();
//
//	struct DefaultVertexMap : public GraphicsMap{
//		virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind);
//	};

protected:
	PathStyle mPathStyle;
};


/// Two-dimensional function plotter
class PlotFunction2D : public Plottable{
public:

	/// @param[in] color	plot color
	PlotFunction2D(const Color& color=Color(0));

	virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind);

//	static GraphicsMap& defaultVertexMap();
//
//	struct DefaultVertexMap : public GraphicsMap{
//		virtual void onMap(GraphicsData& b, const Data& d, const Indexer& ind);
//	};
};



/// Plots data according to one or more attached Plottables
class Plot : public Grid {
public:
	typedef std::vector<Plottable *> Plottables;

	/// @param[in] r	geometry
	Plot(const Rect& r=Rect(0));

	/// @param[in] r	geometry
	/// @param[in] p	plottable
	Plot(const Rect& r, Plottable& p);
	
	/// @param[in] r	geometry
	/// @param[in] p1	first plottable
	/// @param[in] p2	second plottable
	Plot(const Rect& r, Plottable& p1, Plottable& p2);

	Plottables& plottables(){ return mPlottables; }
	const Plottables& plottables() const { return mPlottables; }

	/// Add new plotting routine
	Plot& add(Plottable& v);

	Plot& remove(Plottable& v);

	virtual const char * className() const { return "Plot"; }
	virtual void onDraw(GLV& g);
	virtual bool onEvent(Event::t e, GLV& g);

protected:
	Plottables mPlottables;
//	int mValInd[4];
//	
//	void resetValInd(){
//		for(int i=0; i<4; ++i) mValInd[i]=i;
//	}

//	int valueIndex(int i) const { return mValInd[i]; }

//	Plot& valueIndex(int from, int to){
//		mValInd[from] = to; return *this;
//	}
};


} // glv::
#endif
