/*	Graphics Library of Views (GLV) - GUI Building Toolkit
	See COPYRIGHT file for authors and license information */

#include "glv_preset_controls.h"

namespace glv{


PresetView::PresetView(ModelManager& mm)
:	mMM(&mm)
{
	extent(200);
	addHandler(Event::MouseDrag, Behavior::mouseMove);
}

void PresetView::onDraw(GLV& g){
	using namespace glv::draw;
}

bool PresetView::onEvent(Event::t e, GLV& g){

	switch(e){
	case Event::MouseDown:
	case Event::MouseDrag:
		return false;
	
	case Event::KeyDown:
		switch(g.keyboard().key()){
		default:;
		}
		break;
	
	default:;
	};

	return true;
}


PresetControl::PresetControl()
:	mSearchBox(*this), mMM(NULL), mPrompt(false)
{
	init();
}

PresetControl::PresetControl(ModelManager& m)
:	mSearchBox(*this), mMM(&m), mPrompt(false)
{
	init();
}

void PresetControl::init(){
//	mTextEntry.addHandler(Event::KeyDown, mTextKeyDown);
	mStatus.extent(mSearchBox.h);
	mStatus.disable(Controllable | HitTest | DrawBorder | DrawBack);
	mStatus.symbol(draw::magnifier);
	
//	mBtnPanel.addHandler(Event::MouseDown, mPanelButtonClick);
	mBtnPanel.extent(mStatus.h);
	mBtnPanel.symbol(draw::combo<draw::frameTrunc<1,1,1,1>, draw::crosshatch<2,2> >);
	mBtnPanel.enable(Momentary);
	mBtnPanel.padding(4,0).padding(8,1);
	(*this) << mStatus << mSearchBox;// << mBtnPanel;
	fit();
}


PresetControl::~PresetControl(){
}

//bool PresetControl::PanelButtonClick::onEvent(View& v, GLV& g){
//	//printf("%d\n", pc.mBtnPanel.getValue());
////	if(!pc.mBtnPanel.getValue()){ // flipped since value gets set after event
////		g << pc.mPanel;
////	}
////	else{
////		pc.mPanel.remove();
////	}
//	if(pc.mPanel.parent){ // flipped since value gets set after event
//		pc.mPanel.remove();
//	}
//	else{
//		g << pc.mPanel;
//	}
//
//	return true;
//}


//bool PresetControl::SearchBox::onEvent(Event::t e, GLV& g){
//
//	ModelManager& mm = *pc.mMM;
////	TextView& te = pc.mTextEntry;
//	const Keyboard& k = g.keyboard();
//
//	switch(e){
//	case Event::KeyDown:
//		pc.mStatus.symbol(draw::magnifier);
//		
//		if(k.key() != 's' || !k.ctrl()){
//			pc.mPrompt=false;
//		}
//
//		switch(k.key()){
//		case Key::Down:	// pass on up/down arrows to search list...
//		case Key::Up:
//			mSearchList.onEvent(e,g);
//			return false;
//		case 's':
//			if(k.ctrl()){
//				if(!empty()){
//					const std::string& name = getValue();
//					if(!pc.mPrompt && mm.snapshots().count(name)){
//						pc.mPrompt = true;
//						pc.mStatus.symbol(draw::polygonCut<16,45>);
//						//pc.mStatus.symbol(draw::spokes<8,90>);
//					}
//					else{
//						pc.mPrompt = false;
//						pc.mStatus.symbol(draw::fileSave);
//						mm.saveSnapshot(name);
//						mm.snapshotsToFile();
//					}
//				}
//				return false;
//			}
//			break;
//		case Key::Enter:
//		case Key::Return:
//			if(mSearchList.visible()) setValue(mSearchList.getValue());
//			if(!mm.loadSnapshot(getValue())){
//				printf("Could not load snapshot \"%s\"\n", getValue().c_str());
//			}
//			else{
//				pc.mStatus.symbol(draw::fileLoad);
//			}
//			mSearchList.disable(Visible);
//			return false;
//		case Key::Tab:
//			if(!empty()){
//				const std::string& tstr = getValue();
//				ModelManager::Snapshots::const_iterator it = mm.snapshots().begin();
//				while(it != mm.snapshots().end()){
//					const std::string& s = it->first;
//					int r = strncmp(s.c_str(), tstr.c_str(), tstr.size());
//					if(0 == r){
//						setValue(s);
//						cursorEnd();
//						break;
//					}
//					++it;
//				}
//			}
//			return false;
//		default:;
//		}
//	default:;
//	}
//	
//	bool res = TextView::onEvent(e,g);
//
//	if(Event::KeyDown == e){
//
//		mSearchList.disable(Visible);
//		if(!empty()){
//			std::vector<std::string> items;
//			const std::string& tstr = getValue();
//			ModelManager::Snapshots::const_iterator it = mm.snapshots().begin();
//			while(it != mm.snapshots().end()){
//				const std::string& s = it->first;
//				//int r = strncasecmp(s.c_str(), tstr.c_str(), tstr.size());
//				size_t res = s.find(tstr);
//				if(res != std::string::npos){
////					printf("%s, %d\n", s.c_str(), res);
//					items.push_back(s);
//				}
//				/*
//				The strcasecmp() and strncasecmp() return an integer greater than,
//				equal to, or less than 0, according as s1 is lexicographically
//				greater than, equal to, or less than s2 after translation of each
//				corresponding character to lower-case.  The strings themselves are
//				not modified.  The comparison is done using unsigned characters, so
//				that `\200' is greater than `\0'.
//				*/
////				if(0 == r){
//////					items.push_back(s);
////				}
////				printf("%s\n", s.c_str());
//				++it;
//			}
//
//			if(items.size()){
//				space_t ax = 0, ay = height();
//				toAbs(ax, ay);
//				
//				mSearchList.data().resize(1, items.size());
//				mSearchList.data().assignFromArray(&items[0], items.size());
//				mSearchList.clipIndices();
//				mSearchList.fitExtent();
//				mSearchList.pos(ax,ay);
//				mSearchList.enable(Visible);
//				mSearchList.bringToFront();
//			}
//			if(mSearchList.parent == 0) pc.root() << mSearchList;			
//		}
//	}	
//
//	return res;
//}
//
//bool PresetControl::SearchBox::SearchList::onEvent(Event::t e, GLV& g){
//	const Keyboard& k = g.keyboard();
//
//	switch(e){
//	case Event::KeyDown:
//		switch(k.key()){
//		case Key::Enter:
//		case Key::Return:
//			sb.setValue(getValue());
//			sb.onEvent(e,g);
//			break;
//		default:;
//		}
//		break;
//	case Event::FocusLost:
//		disable(Visible);
//		break;
//	default:;
//	}
//	return ListView::onEvent(e,g);
//}

bool PresetControl::PresetSearchBox::onEvent(Event::t e, GLV& g){

	if(NULL != pc.mMM){

	ModelManager& mm = *pc.mMM;
	const Keyboard& k = g.keyboard();

	if(Event::KeyDown == e){
		items().clear();
		ModelManager::Snapshots::const_iterator it = mm.snapshots().begin();
		while(it != mm.snapshots().end()){
			addItem(it->first);
			++it;
		}
	}

	switch(e){
	case Event::KeyDown:
		pc.mStatus.symbol(draw::magnifier);
		
		if((k.key() != 's' && k.key() != Key::Delete) || !k.ctrl()){
			pc.mPrompt=false;
		}

		switch(k.key()){
		case 's':
			if(k.ctrl()){
				if(!empty()){
					const std::string& name = getValue();
					if(!pc.mPrompt && mm.snapshots().count(name)){
						pc.mPrompt = true;
						pc.mStatus.symbol(draw::question);
						//pc.mStatus.symbol(draw::polygonCut<16,45>);
						//pc.mStatus.symbol(draw::spokes<8,90>);
					}
					else{
						pc.mPrompt = false;
						pc.mStatus.symbol(draw::fileSave);
						mm.saveSnapshot(name);
						mm.snapshotsToFile();
					}
				}
				return false;
			}
			break;
		case Key::Backspace:
		case Key::Delete:
			if(k.ctrl()){
				if(!empty()){
					const std::string& name = getValue();
					if(mm.snapshots().count(name)){
						if(!pc.mPrompt){
							pc.mPrompt = true;
							pc.mStatus.symbol(draw::question);
						}
						else{
							pc.mPrompt = false;
							pc.mStatus.symbol(draw::x);
							mm.snapshots().erase(name);
							mm.snapshotsToFile();
						}					
					}

				}
				return false;
			}
			break;
		case Key::Enter:
		case Key::Return:
			if(!listShowing()){ // only attempt load if not selecting from list
				if(!mm.loadSnapshot(getValue())){
					printf("Could not load snapshot \"%s\"\n", getValue().c_str());
				}
				else{
					pc.mStatus.symbol(draw::fileLoad);
				}
			}
			break;
		default:;
		}
	default:;
	}
	
	} // NULL != mMM

	bool res = SearchBox::onEvent(e,g);

	return res;
}


bool PresetControl::setPreset(const std::string& v){
	if(NULL != mMM && mMM->snapshots().count(v)){
		mMM->loadSnapshot(v);
		mSearchBox.setValue(v);
		mSearchBox.cursorEnd();
		return true;		
	}
	return false;
}


bool PresetControl::loadFile(){
	if(NULL == mMM){
		fprintf(stderr, "From PresetControl::loadFile: Attempt to load file without a ModelManager\n");
	}
	else if(mMM->snapshotsFromFile()){
		const std::string name = "default";
		if(mMM->snapshots().count(name)){
			mMM->loadSnapshot(name);
			mSearchBox.setValue(name);
			mSearchBox.cursorEnd();
		}
		return true;
	}
	return false;
}

void PresetControl::onDraw(GLV& g){
	using namespace glv::draw;

//	if(mPrompt)	mStatus.symbol(draw::polygonCut<16,45>);
//	else			mStatus.symbol(0);
	
	//mPanel.property(Visible, mBtnPanel.getValue());

}

bool PresetControl::onEvent(Event::t e, GLV& g){

	switch(e){
	case Event::MouseDown:
	case Event::MouseDrag:
		return false;
	
	case Event::KeyDown:
		switch(g.keyboard().key()){
		default:;
		}
		break;
	
	default:;
	};

	return true;
}




template <class T>
static void insertCopy(std::vector<T>& src, int to, int from){
	if(src.empty()){
		src.push_back(T());
	}
	else{
		src.insert(src.begin() + to, src[from]);
	}
}

PathView::PathView()
:	Widget(Rect(400, 20)),
	mStates(0),
	mDur(2,4,80,0), mCrv(3,3, 800, -800), mSmt(1,0,1,0), // mName(Rect(200,12), 6)
	mPos(0), mPlaying(false)
{
//	data().resize(Data::STRING);
//	data().resize(Data::NONE).shape(1,8);
//	data().print();
	disable(DrawSelectionBox);
//	enable(DrawSelectionBox);
	enable(CropChildren);
	disable(DrawGrid);

	mDur.l = seqRight();
	mCrv.l = mDur.right();
	mSmt.l = mCrv.right();
	mName.l= mSmt.right()+8;
	
	mDur.disable(DrawBorder | DrawBack);
	mCrv.disable(DrawBorder);
	mSmt.disable(DrawBorder);
	mName.disable(DrawBorder);
	mName.searchBox().disable(DrawBorder);
	
//	mPathMM.add("dur", mDur);
//	mPathMM.add("crv", mCrv);
//	mPathMM.add("smt", mSmt);
//	mPathMM.add("name", mName);

	(*this) << mDur << mCrv << mSmt << mName;
}


PathView& PathView::modelManager(ModelManager& v){
	mStates = &v;
	mName.modelManager(v);
	return *this;
}


void PathView::onAnimate(double dsec, GLV& g){
	if(mPlaying && mPath.size()>0){

		double max = mPath.size()-1;

		if(mPos >= max){		// clip current position
			mPos = max;
		}
		else if(mStates){		// are there presets assigned?				
			int idx0 = loadCurrentPos();
			float dur = mPath[idx0].dur;
//			printf("dur = %g, dt = %g\n", dur, dsec);
			if(dur > dsec){
				mPos += dsec/dur;
			}
			else{
				++mPos;
				onAnimate(dsec, g);
			}
		}
	}
}

void PathView::drawHeader(float x, float y){
//	float y =-10 + 0.;
//	float x = 0.;
	float textSize = 6;
	draw::text("dur" , mDur.l + x, y, textSize);
	draw::text("crv" , mCrv.l + x, y, textSize);
	draw::text("s" , mSmt.l + x, y, textSize);
	draw::text("name", mName.l+ x, y, textSize);
}

template <int D>
static void pointerLine(float l, float t, float r, float b){
	float h2 = (t+b)/2;
	float pts[] = {
		D, h2,
		0, h2-D,
		0, h2+D,
		D, h2,
		r, h2
	};
	draw::paint(draw::LineStrip, (Point2*)pts, GLV_ARRAY_SIZE(pts)/2);
}

void PathView::onDraw(GLV& g){

	if(NULL == mStates) return;

	int Nk = mPath.size();

	data().shape(1,Nk);
	
	{
		//drawHeader(0, 0);

		// draw selected row highlight
		draw::color(Color(colors().text, 0.1));
		draw::frame(0, selected()*dy(), right(), (selected()+1)*dy());
			
		// draw start cursor
		draw::color(colors().selection);
		float pixStart = draw::pixc(mStart*dy());
		pointerLine<6>(l,pixStart-8, right(),pixStart+8);
	
		// draw position indicator
		draw::color(colors().selection);
		draw::rectTrunc<2,2,2,2>(2, dy()*mPos, seqRight()-2, dy()*(mPos+1));

		Rect vrect = visibleRegion();
//		vrect.print();

		int jbeg = vrect.top()   /dy();
		int jend = (vrect.bottom()/dy()) + 1;
		if(jend > sizeY()) jend = sizeY();
		
//		draw::color(1,0,0);
//		draw::x(vrect.left(), vrect.top(), vrect.right(), vrect.bottom());			
//		printf("%d %d\n", jbeg, jend);

		draw::color(colors().text);
		draw::stroke(1);
		std::string s;
//		float px = 0.375, py = 0.375;
		float px = 0.5, py = 0.5;
		
		for(int j=jbeg; j<jend; ++j){
			float y = getY(j) + py;
			toString(s, j, "%03i");	draw::text(s.c_str(), px+startRight(), y+2, 6);

			if(selected() != j){
				Keyframe& kf = mPath[j];
				toString(s, kf.dur);		draw::text(s.c_str(), mDur.l + px, y);
				toString(s, kf.crv, "% g");	draw::text(s.c_str(), mCrv.l + px, y);
				toString(s, kf.smt);		draw::text(s.c_str(), mSmt.l + px, y);
				draw::text(kf.name.c_str(), mName.l, y);
			}
		}
	}
	
//	int numBytes = data().resize(1, Nk);
//	if(0 != numBytes){
//		
//	}

//	const ModelManager::Snapshots& keys = mPathMM.snapshots();
//	int Ns = keys.size();
//	
//	int numBytes = data().resize(Data::STRING, 1, Ns);
//	if(0 != numBytes){
//		
//		ModelManager::Snapshots::const_iterator it = keys.begin();
//		int idx=0; // local array index
//		
//		while(keys.end() != it){
//			data().assign<std::string>(it->first, 0, idx);
//			++idx;
//			++it;
//		}
//	}
	
	//printf("resize: %d\n", numBytes);

	fitExtent();

	Widget::onDraw(g);
}

bool PathView::onEvent(Event::t e, GLV& g){
	//if(Event::MouseDown == e) selectFromMousePos(g);
	
	const Keyboard& k = g.keyboard();
	const Mouse& m = g.mouse();
	
	switch(e){
	case Event::KeyDown:
		switch(k.key()){
		case 'd':
			if(k.ctrl()){
				// duplicate currently selected frame
				insertCopy(mPath, selected()+1, selected());
				return false;
			}
			break;
		case 's':
			if(k.ctrl()){
				saveFile();
				return false;
			}
			break;

		case 'l':
			if(k.ctrl()){
				loadFile();
				return false;
			}
			break;
		case ' ':	// toggle playback
			mPlaying ^= 1;
			break;
		case Key::Enter:
		case Key::Return:
			mPos = mStart;
			break;
			
		default:;
		}
		break;

	case Event::MouseDown:
	case Event::MouseDrag:
		{
			float mx = m.xRel();
			float my = m.yRel();
			//printf("%d\n", yi);
			if(e == Event::MouseDown && mx >= seqRight()){
				selectFromMousePos(g);
			}
			else if(mx <= startRight()){
				int yi = my / dy();
				mStart = glv::clip<int>(yi, mPath.size()-1);
			}
			else{
				float y = my / dy();
				mPos = glv::clip<float>(y, mPath.size()-1);
				loadCurrentPos();			
			}
		}
		break;
	default:;
	}
	
	bool res = Widget::onEvent(e,g);
	return res;
}

void PathView::onCellChange(int iOld, int iNew){
	float y = iNew * dy();
	mDur.t = getY(iNew);
	mCrv.t = getY(iNew);
	mSmt.t = getY(iNew);
	mName.t= y;

	Keyframe& kf = mPath[iNew];
	
	mDur.data().set(kf.dur);
	mCrv.data().set(kf.crv);
	mSmt.data().set(kf.smt);
	mName.searchBox().data().set(kf.name);
	mName.searchBox().setValue(mName.searchBox().getValue());
	mName.searchBox().selectAll();
}

std::string PathView::pathsName() const {
	return (mStates ? mStates->name() : "") + "Paths";
}

void PathView::loadFile(){
	ModelManager& mm = mPathMM;

	mm.clearModels();
	mm.clearSnapshots();
	mm.name(pathsName());

	DataModel len, dur, crv, smt, name;
	
	len.data().resize(Data::INT, 1);	
	
	mm.add("len", len);
	
	//len.data().elem<int>(0) = 5;
	//len.data().print();

	mm.snapshotsFromFile();
//	printf("num snapshots = %d\n", mm.snapshots().size());

//	mm.printSnapshots();

	//(mm.snapshots()["path"]["len"])->data().print();
	if(!mm.loadSnapshot("path")) printf("error loading path snapshot\n");

//	len.data().print();

	int N = len.data().elem<int>(0);

//	printf("%s\n", mm.snapshotsToString().c_str());
//	printf("%d\n", N);

	mm.add("dur", dur);
	mm.add("crv", crv);
	mm.add("smt", smt);
	mm.add("name", name);
	
	dur.data().resize(Data::FLOAT, N);
	crv.data().resize(Data::FLOAT, N);
	smt.data().resize(Data::FLOAT, N);
	name.data().resize(Data::STRING, N);
	
	mm.snapshotsFromFile();
	mm.loadSnapshot("path");
//	mm.printSnapshots();

	mPath.resize(N);
	for(int i=0; i<N; ++i){
		Keyframe& kf = mPath[i];
		kf.dur = dur.data().elem<float>(i);
		kf.crv = crv.data().elem<float>(i);
		kf.smt = smt.data().elem<float>(i);
		kf.name=name.data().elem<std::string>(i);
	}
}

void PathView::saveFile(){
	ModelManager& mm = mPathMM;

	mm.name(pathsName());

	DataModel len, dur, crv, smt, name;
	
	int N = mPath.size();
	
	len.data().resize(Data::INT, 1);
	dur.data().resize(Data::FLOAT, N);
	crv.data().resize(Data::FLOAT, N);
	smt.data().resize(Data::FLOAT, N);
	name.data().resize(Data::STRING, N);
	
	len.data().assign(N);
	for(int i=0; i<N; ++i){
		const Keyframe& kf = mPath[i];
		dur.data().assign(kf.dur, i);
		crv.data().assign(kf.crv, i);
		smt.data().assign(kf.smt, i);
		name.data().assign(kf.name, i);
	}
	
	mm.clearModels();
	mm.clearSnapshots();
	
	mm.add("len", len);
	mm.add("dur", dur);
	mm.add("crv", crv);
	mm.add("smt", smt);
	mm.add("name", name);
	
	mm.saveSnapshot("path");
	mm.snapshotsToFile();
}


void PathView::fitExtent(){
	int N = mPath.size();
	if(!N) N=1;
	extent(w, N*mName.h);
}


int PathView::loadCurrentPos(){
	int idx0 = int(mPos);
	
	if(idx0 >= int(mPath.size()-1)){
		mStates->loadSnapshot(mPath[idx0].name);
	}
	else{		
		int idx1 = idx0 + 1;
		float frac = mPos - idx0;
		
		// warp fraction
		float crv = mPath[idx0].crv;
		float smt = mPath[idx0].smt;
		frac = warp(frac, crv, smt);
	
		const std::string& name0 = mPath[idx0].name;
		const std::string& name1 = mPath[idx1].name;
//		printf("%s -> %s, %g\n", name0.c_str(), name1.c_str(), frac);
		mStates->loadSnapshot(name0, name1, 1-frac, frac);
	}
	return idx0;
}

float PathView::warp(float x, float crv, float smt){
	static const float eps = 1e-8;
	if(crv>eps || crv<-eps){	// avoid divide by zero when c is near 0
		x = (1.f - exp(-crv*x))/(1.f - exp(-crv));
	}
	if(smt>0){
		x = x*x*(3.f - 2.f*x);
	}
	return x;
}




PathEditor::PathEditor(space_t hei)
:	Table("<")
{
	mPathView.attach(ntSelection, Update::Selection, this);
	
	mPathPresetControl.modelManager(mPathView.mPathMM);
	
	mHeader.h = 10;
	mScroll.extent(mPathView.w, hei);
	mScroll.mode(Scroll::VERTICAL);
	(*this) << mPathPresetControl << mHeader << (mScroll << mPathView);
	arrange();
}

void PathEditor::onDraw(GLV& g){
	draw::color(colors().text);
	mPathView.drawHeader(0, mHeader.top()+2);
}

void PathEditor::ntSelection(const Notification& n){
	PathView& S = *n.sender<PathView>();
	PathEditor& R = *n.receiver<PathEditor>();
	const ChangedSelection& D = *n.data<ChangedSelection>();

	Rect vrect = S.visibleRegion();
	int itop = vrect.top() / S.dy();
	int ibot = vrect.bottom() / S.dy();
	//int isel = snd.selected();

//	printf("%d %d\n", itop, ibot);

	if(D.newIndex <= itop || D.newIndex >= ibot){
		//mScroll.pageY(-1);
		//rcv.mScroll.scrollY(-snd.dy());
		R.mScroll.scrollTopTo(D.newIndex * S.dy());
		R.mScroll.pageY(0.5);
	}
}





} // glv::
