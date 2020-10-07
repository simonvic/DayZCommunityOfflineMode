/*
	Manages all keybinds for COM
*/
class CustomDebugMonitor extends Module{
	protected bool m_IsVisible = false;
	protected ref ArkDebugMonitor m_debugMonitor;
	
	protected ref TVectorArray m_canvasPoints;
	protected float m_time = 0;	
	protected float m_timeMultipler = 100;

	void CustomDebugMonitor(){
	    m_debugMonitor = new ArkDebugMonitor;
		m_canvasPoints = new TVectorArray;
		m_canvasPoints.Insert("0 0 0"); //first point (only x and y is used)

	}

	void ~CustomDebugMonitor(){
	}
	
	override void Init(){
		super.Init();

		m_debugMonitor.Init();
		m_debugMonitor.Hide();
	}
	
	override void onUpdate( float timeslice ){		
        if( m_IsVisible ){
            PlayerBase player = PlayerBase.Cast( COM_GetPB() );
            if ( player ){
                DebugMonitorValues values = player.GetDebugMonitorValues();
                if ( values ){
                	updateDebugMonitorValues(player,values);    
                }
				m_time += timeslice;
				drawHeartRate(player);
				//drawGaussFunction();
				//drawDampedSinFunction();
				//drawArctan();
				m_debugMonitor.updateHeartStats(player.getHeartRateManager());
            }
        }
	}
	
	private void drawHeartRate(PlayerBase player){
		if(m_time *  m_timeMultipler > m_debugMonitor.getCanvasScreenWidth()) {
			m_time = 0;
			m_canvasPoints.Clear();
		}
		
		vector newPoint;
		newPoint[0] = m_time * m_timeMultipler;
		newPoint[1] = player.getHeartRateManager().getHeartRate();
		newPoint[2] = 0;	
		
		m_canvasPoints.Insert(newPoint);
		m_debugMonitor.clearCanvas();
		m_debugMonitor.drawLines(m_canvasPoints);
	}
	
	private void drawGaussFunction(){
		if(m_time *  m_timeMultipler > m_debugMonitor.getCanvasScreenWidth()) {
			m_time = 0;
			m_canvasPoints.Clear();
		}
		
		vector newPoint;
		newPoint[0] = m_time * m_timeMultipler;
		newPoint[1] = SMath.Gauss(1,3,1,m_time) * m_timeMultipler;
		newPoint[2] = 0;	
		
		m_canvasPoints.Insert(newPoint);
		m_debugMonitor.clearCanvas();
		m_debugMonitor.drawLines(m_canvasPoints);
	}
	
	private void drawDampedSinFunction(){
		if(m_time *  m_timeMultipler > m_debugMonitor.getCanvasScreenWidth()) {
			m_time = 0;
			m_canvasPoints.Clear();
		}
		
		vector newPoint;
		newPoint[0] = m_time * m_timeMultipler;
		newPoint[1] = SMath.DampedSin(m_debugMonitor.getCanvasScreenHeight()/2, 0.8, 0, 10, m_debugMonitor.getCanvasScreenHeight()/2, m_time);
		newPoint[2] = 0;	
		
		m_canvasPoints.Insert(newPoint);
		m_debugMonitor.clearCanvas();
		m_debugMonitor.drawLines(m_canvasPoints);

	}
	
	private void drawArctan(){
		if(m_time *  m_timeMultipler > m_debugMonitor.getCanvasScreenWidth()) {
			m_time = 0;
			m_canvasPoints.Clear();
		}
		
		float result = SMath.Arctan(-47.5, 0.05, -9.1, 103.6, m_time * m_timeMultipler);
		vector newPoint;
		newPoint[0] = m_time * m_timeMultipler;
		newPoint[1] = result;
		newPoint[2] = 0;	
		
		m_canvasPoints.Insert(newPoint);
		m_debugMonitor.clearCanvas();
		m_debugMonitor.drawLines(m_canvasPoints);
	}
	
	private void updateDebugMonitorValues(PlayerBase player, DebugMonitorValues values){
		auto health = player.GetHealth("","Health");
		auto blood = player.GetHealth("","Blood");
		auto lastdamage = values.GetLastDamage();
		
		if( lastdamage == "" )
		{
		    lastdamage = "Unknown";
		}
		
		auto position = player.GetPosition();
		auto orientation = GetGame().GetCurrentCameraDirection().VectorToAngles();
		
		m_debugMonitor.SetHealth( health );
		m_debugMonitor.SetBlood( blood );
		m_debugMonitor.SetLastDamage( lastdamage );
		m_debugMonitor.SetPosition( position );
		m_debugMonitor.SetOrientation( orientation );
		
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		
		string date = day.ToStringLen(2) + "-" + month.ToStringLen(2) + "-" + year.ToStringLen(2) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
		
		m_debugMonitor.SetDateTime( date );
	}
	
	override void RegisterKeyMouseBindings() 
	{
		auto oToggleMonitor = new KeyMouseBinding( GetModuleType(), "ToggleMonitor", "Toggles the debug monitor." );

		oToggleMonitor.AddBinding( "kB" );

		RegisterKeyMouseBinding( oToggleMonitor );
	}

    void ToggleMonitor()
    {
        m_IsVisible = !m_IsVisible;

        if( m_IsVisible )
        {
            m_debugMonitor.Show();
        }
        else
        {
            m_debugMonitor.Hide();
        }
    }
}