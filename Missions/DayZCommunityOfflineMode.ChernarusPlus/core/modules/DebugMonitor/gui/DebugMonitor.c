class ArkDebugMonitor
{
	private Widget m_WidgetRoot;
	private TextWidget m_pWindowLabelText;
	private TextListboxWidget m_pNamesListboxWidget;
	private TextListboxWidget m_pValuesListboxWidget;
	private MultilineTextWidget m_pModifiersMultiTextWidget;
	
	private CanvasWidget m_canvasHeartRate;
	private float m_canvasWidth;
	private float m_canvasHeight;
	
	private TextWidget m_startX;
	private TextWidget m_startY;
	private TextWidget m_endX;
	private TextWidget m_endY;
	
	private TextWidget m_heartRate;
	private TextWidget m_epinephrine;
	

	void ArkDebugMonitor()
	{
		m_WidgetRoot = GetGame().GetWorkspace().CreateWidgets("$CurrentDir:missions\\DayZCommunityOfflineMode.ChernarusPlus\\core\\modules\\DebugMonitor\\gui\\layouts\\day_z_debug_monitor.layout");
		m_WidgetRoot.Show(false);

		m_pWindowLabelText = TextWidget.Cast( m_WidgetRoot.FindAnyWidget("WindowLabel") );
		m_pNamesListboxWidget = TextListboxWidget.Cast( m_WidgetRoot.FindAnyWidget("NamesListboxWidget") );
		m_pValuesListboxWidget = TextListboxWidget.Cast( m_WidgetRoot.FindAnyWidget("ValuesListboxWidget") );
		m_pModifiersMultiTextWidget = MultilineTextWidget.Cast( m_WidgetRoot.FindAnyWidget("ModifiersMultilineTextWidget") );
		
		m_canvasHeartRate = CanvasWidget.Cast(m_WidgetRoot.FindAnyWidget("canvas_heartRate"));
		m_canvasHeartRate.GetScreenSize(m_canvasWidth,m_canvasHeight);
		
		m_startX = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("txt_startX"));
		m_startY = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("txt_startY"));
		m_endX = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("txt_endX"));
		m_endY = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("txt_endY"));
		
		m_heartRate = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("txt_heartRate"));
		m_epinephrine = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("txt_epinephrine"));
		
	}

	void Init()
	{
		m_pNamesListboxWidget.AddItem("HEALTH:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);

		m_pNamesListboxWidget.AddItem("BLOOD:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);

		/*m_pNamesListboxWidget.AddItem("BODY TEMP:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);*/

		m_pNamesListboxWidget.AddItem("LAST DAMAGE:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);

		m_pNamesListboxWidget.AddItem("POSITION:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);

		m_pNamesListboxWidget.AddItem("ORIENTATION:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);

		m_pNamesListboxWidget.AddItem("DATETIME:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);

        string version;
        GetGame().GetVersion(version);

		m_pNamesListboxWidget.AddItem("VERSION:", NULL, 0);
		m_pValuesListboxWidget.AddItem( " " + version, NULL, 0);

		/*m_pNamesListboxWidget.AddItem("MODIFIERS:", NULL, 0);
		m_pValuesListboxWidget.AddItem("", NULL, 0);*/

		//m_DebugFloatsListWidget.AddItem(key,NULL,0);
		//m_DebugFloatsListWidget.SetItem(i,value.ToString(),NULL,1);
		
		m_WidgetRoot.Show(true);
	}

	void SetHealth(float value)
	{
		string health = string.Format(" %1", value.ToString());
		m_pValuesListboxWidget.SetItem(0, health, NULL, 0);
	}

	void SetBlood(float value)
	{
		string blood = string.Format(" %1", value.ToString());
		m_pValuesListboxWidget.SetItem(1, blood, NULL, 0);
	}

	void SetLastDamage(string value)
	{
		string lastDamage = string.Format(" %1", value);
		m_pValuesListboxWidget.SetItem(2, lastDamage, NULL, 0);
	}

	void SetPosition(vector value)
	{
		string position = string.Format(" %1 %2 %3", value[0].ToString(), value[1].ToString(), value[2].ToString());
		m_pValuesListboxWidget.SetItem(3, position, NULL, 0);
	}

	void SetOrientation(vector value)
	{
		string orientation = string.Format(" %1 %2 %3", value[0].ToString(), value[1].ToString(), value[2].ToString());
		m_pValuesListboxWidget.SetItem(4, orientation, NULL, 0);
	}

	void SetDateTime(string value)
	{
		string orientation = string.Format(" %1", value);
		m_pValuesListboxWidget.SetItem(5, orientation, NULL, 0);
	}

	void Hide()
	{
		m_WidgetRoot.Show(false);
	}

	void Show()
	{
		m_WidgetRoot.Show(true);
	}
	
	void clearCanvas(){
		m_canvasHeartRate.Clear();	
	}
	
	// inverse y?
	void drawLines(TVectorArray points){
		
		int pointsCount = points.Count();
		for (int i = 0; i < pointsCount; i++){
			vector lastPoint;
			vector nextPoint;
			if (i == 0) {
				lastPoint = "0 0 0";
			}else{	
				lastPoint = points.Get(i - 1);
				nextPoint = points.Get(i);
			}
			drawLine(lastPoint[0],m_canvasHeight-lastPoint[1],nextPoint[0],m_canvasHeight-nextPoint[1]);			
		}
	}
	
	void drawLine(float startX, float startY, float endX, float endY ){
		m_startX.SetText("Start X: " + startX);
		m_startY.SetText("Start Y: " + startY);
		m_endX.SetText("End X: " + endX);
		m_endY.SetText("End Y: " + endY);
		m_canvasHeartRate.DrawLine(startX,startY,endX,endY, 2, COLOR_RED);
	}
	
	void updateHeartStats(HeartRateManager hrManager){
		m_heartRate.SetText("Heartrate(BPM): " + hrManager.getHeartRate());
		m_epinephrine.SetText("Epinephrine(mg): " + hrManager.getEpinephrine());
	}
	
	float getCanvasScreenWidth(){
		return m_canvasWidth;
	}
	
	float getCanvasScreenHeight(){
		return m_canvasHeight;
	}

};