class DebugMenu extends PopupMenu{

	protected PlayerBase m_player;
	protected SliderWidget m_slider_specialty;
	protected TextWidget m_sliderValue_specialty;
	
	protected TextWidget m_txt_playerWeight;
	protected const string PLAYER_WEIGHT_TXT = "Current carried weight = %1 grams";
	
	void DebugMenu(){
		m_player = PlayerBase.Cast(GetGame().GetPlayer());
	}

	void ~DebugMenu(){
	}


	override void Init(){
		m_slider_specialty = SliderWidget.Cast(layoutRoot.FindAnyWidget("slider_specialty"));
		m_slider_specialty.SetCurrent(m_player.GetSoftSkillsManager().GetSpecialtyLevel());
		m_sliderValue_specialty = TextWidget.Cast(layoutRoot.FindAnyWidget("sliderValue_specialty"));
		m_sliderValue_specialty.SetText(m_slider_specialty.GetCurrent().ToString());
		
		m_txt_playerWeight = TextWidget.Cast(layoutRoot.FindAnyWidget("txt_playerWeight"));
		m_txt_playerWeight.SetText(string.Format(PLAYER_WEIGHT_TXT, m_player.GetWeight()));
	}
	
	override bool OnChange(Widget w, int x, int y, bool finished){
		
		if(w && w.IsInherited( SliderWidget )){
			SliderWidget s = SliderWidget.Cast(w);
			
			switch(s.GetName()){
				case "slider_specialty" :{
					updateSpecialty(s.GetCurrent());
					break;
				}
				default: SLog.w("No slider widget name found.","DebugMenu");
			}
		}
		
		return true;
	}
	
	protected void updateSpecialty(float value){
		value = Math.Clamp(value, -1, 1);
		m_player.GetSoftSkillsManager().SetSpecialtyLevel(value);
		m_sliderValue_specialty.SetText(value.ToString());
	}

	override void OnShow(){
		
	}

	override void OnHide(){
		
	}

	override bool OnClick( Widget w, int x, int y, int button ){
		return false;
	}
	
	

}