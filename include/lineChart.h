/*
 * lineChart.h
 *
 *  Created on: May 24, 2009
 *      Author: brent
 */

#ifndef LINECHART_H_
#define LINECHART_H_
#include "wx/wxprec.h"
#include "datalogData.h"
#include <wx/dynarray.h>


class Range{

public:

	Range(double min, double max, size_t precision, wxString label) :
		m_min(min),
		m_max(max),
		m_precision(precision),
		m_label(label)
	{ }

	double GetMin(){ return m_min; }
	double GetMax(){ return m_max; }
	size_t GetPrecision(){ return m_precision; }
	wxString & GetLabel(){ return m_label; }

private:
	double m_min;
	double m_max;
	size_t	m_precision;
	wxString m_label;
};

#include <wx/dynarray.h>

WX_DEFINE_ARRAY_DOUBLE(double, SeriesValues);

class Series{

public:

	Series(size_t bufferSize, int rangeId, size_t offset, wxString label, wxColor color, int precision);

	const static double NULL_VALUE = -0xFFFFFFFFFFFFFFF;
	const static size_t DEFAULT_LOOK_DISTANCE = 100;
	SeriesValues * GetSeriesValues();
	int GetRangeId();
	void SetRangeId(int seriesId);
	int GetOffset();
	void SetOffset(int offset);
	wxString & GetLabel();
	void SetLabel(wxString label);
	void SetColor(wxColor color);
	wxColor GetColor();
	int GetPrecision();
	void SetPrecision(int precision);

	size_t GetBufferSize();
	void SetBufferSize(size_t size);
	double GetValueAtOrNear(size_t index);
	double GetValueAt(size_t index);
	void SetValueAt(size_t index, double value);

private:

	int m_rangeId;
	int m_offset;
	wxString m_label;
	wxColor m_color;
	int m_precision;
	SeriesValues m_seriesValues;
};

WX_DECLARE_OBJARRAY(Range*,RangeArray);
WX_DECLARE_STRING_HASH_MAP(Series*,SeriesMap);

class LineChart : public wxWindow
{
	public:
		enum SCALE_DISPLAY_ORIENTATION{
			ORIENTATION_LEFT,
			ORIENTATION_RIGHT
		};

		LineChart();
		LineChart(wxWindow *parent,
			wxWindowID id = -1,
			const wxPoint &pos = wxDefaultPosition,
			const wxSize &size = wxDefaultSize);

		~LineChart();

		static const int TIMESPAN_FROM_NOW = 0;
		static const int TIMESPAN_FROM_LAST_LOG_ENTRY = 1;

		void SetChartHistorySize(unsigned int chartHistorySize);

		void OnEraseBackground(wxEraseEvent& event);

		int GetChartWidth();

		void SetLogBufferSize(int size);
		int GetLogBufferSize();
		size_t GetMaxSeriesBufferSize();

		void SetZoom(int zoomPercentage);
		int GetZoom();

		void SetTimespanMode(int mode);
		int GetTimespanMode();

		bool GetShowScale();
		void ShowScale(bool showScale);

		void SetViewOffsetFactor(double offset);
		double GetViewOffsetPercent();

		size_t GetMarkerIndex();
		void SetMarkerIndex(size_t index);

		int AddRange(Range *range);
		void ClearAllSeries();
		void AddSeries(wxString channel, Series *series);
		Series * GetSeries(wxString channel);

		DECLARE_EVENT_TABLE()

	protected:
		void OnPaint( wxPaintEvent &event );
		void OnSize( wxSizeEvent &event );
		void OnMouseEnter(wxMouseEvent &event);
		void OnMouseDoubleClick(wxMouseEvent &event);
		void OnMouseExit(wxMouseEvent &event);
		void OnMouseMove(wxMouseEvent &event);

	private:

		void DrawGrid(wxMemoryDC &dc);
		int DrawScale(wxMemoryDC &dc);
		void DrawMouseoverMarker(wxMemoryDC &dc);
		void DrawCurrentValues(wxMemoryDC &dc, size_t dataIndex, int x, int y);

		SeriesMap			m_seriesMap;
		RangeArray			m_rangeArray;

		double				m_viewOffsetFactor;
		size_t				m_markerIndex;

		int					_zoomPercentage;
		int					_currentWidth;
		int					_currentHeight;
		wxBitmap 			*_memBitmap;
		wxColor				_backgroundColor;
		bool				m_showScale;

		bool				m_showData;
		int					m_mouseX;
		int					m_mouseY;
		int					m_leftEdge;

};
#endif /* LINECHART_H_ */
