class PPEMenu extends PopupMenu{
	
	protected TextListboxWidget m_list_registeredAnimations;
	
	protected TextListboxWidget m_list_playingAnimations;
	protected TextListboxWidget m_list_pausedAnimations;
	protected TextListboxWidget m_list_stoppedAnimations;
	
	protected ButtonWidget m_btn_start;
	protected ButtonWidget m_btn_stop;
	protected ButtonWidget m_btn_pause;
	protected ButtonWidget m_btn_resume;
	protected ButtonWidget m_btn_deactivateAll;
	
	protected ref Timer m_updateTimer = new Timer();
	protected static ref TPPEAnimatedParamsList m_registeredAnimations = new TPPEAnimatedParamsList;
	
	protected static ref PPEExhaustedAnimation m_exhaust = new PPEExhaustedAnimation(3);
	protected static ref PPEDebugAnimation m_debug  = new PPEDebugAnimation();
	protected static ref PPEHitReceivedAnimation m_hit = new PPEHitReceivedAnimation(3);
	protected static ref PPEEpinephrineAnimation m_epinephrine = new PPEEpinephrineAnimation();

	void PPEMenu(){
		
	}
	
	void ~PPEMenu(){
	}
	
	
	override void Init(){
		registerAnimations();
		m_list_registeredAnimations = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("list_registered"));
		loadRegisteredAnimations();
		m_list_playingAnimations = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("list_playing"));		
		m_list_pausedAnimations = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("list_paused"));
		m_list_stoppedAnimations = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("list_stopped"));
		
		m_btn_start = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_start"));
		m_btn_stop = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_stop"));
		m_btn_pause = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_pause"));
		m_btn_resume = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_resume"));
		m_btn_deactivateAll = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btn_deactivateAll"));
		
		m_updateTimer.Run(0.1,this,"updateAnimations",NULL, true);
	}
	
	protected void registerAnimations(){
		m_registeredAnimations.Clear();
		m_registeredAnimations.InsertAt(m_exhaust, 0);
		m_registeredAnimations.InsertAt(m_debug, 1);
		m_registeredAnimations.InsertAt(m_hit, 2);
		m_registeredAnimations.InsertAt(m_epinephrine, 3);
		SLog.i(string.Format("Registered %1 animations",m_registeredAnimations.Count()), "PPEMenu",0);
	}
	
	protected void loadRegisteredAnimations(){
		foreach(auto anim : m_registeredAnimations){
			string animName = anim.Type().ToString() + "(";
			string animSuperType;
			if(anim.IsInherited(PPELoopedParams)) {
				animSuperType = "PPELoopedParams";
				}else if(anim.IsInherited(PPETimedParams)){
				animSuperType = "PPETimedParams";
			}
			animName += animSuperType + ")";
			m_list_registeredAnimations.AddItem(animName,anim,0);
			SLog.i(string.Format("Loading registered animation: %1",anim), "",1);
		}
	}
	
	override void OnShow(){
		SLog.i("Resuming animations update","PPEMenu",0);
		m_updateTimer.Continue();
	}
	
	void updateAnimations(){
		autoptr TPPEAnimatedParamsList anims = PluginPPEffects.getAnimations();
		TextListboxWidget destination;
		m_list_playingAnimations.ClearItems();
		m_list_stoppedAnimations.ClearItems();
		m_list_pausedAnimations.ClearItems();
		foreach(auto anim : anims){
			ePPEAnimationStates animState = anim.getAnimationState();
			switch(animState){
				case ePPEAnimationStates.PLAYING:
				destination = m_list_playingAnimations;
				break;
				
				case ePPEAnimationStates.STOPPED:
				destination = m_list_stoppedAnimations;
				break;
				
				case ePPEAnimationStates.PAUSED:
				destination = m_list_pausedAnimations;
				break;
				
				default:
				SLog.w("Unkown PPEAnimation state","PPEMenu");
				destination = m_list_pausedAnimations;
			}
			destination.AddItem(anim.Type().ToString(),anim,0);
		}
	}
	
	override void OnHide(){
		SLog.i("Pausing animations update","PPEMenu",0);
		m_updateTimer.Pause();
	}
	
	override bool OnClick( Widget w, int x, int y, int button ){
		string selection;
		int selectedRow = m_list_registeredAnimations.GetSelectedRow();
		if (  selectedRow != -1 ){
			m_list_registeredAnimations.GetItemText( selectedRow, 0, selection );
		}
		
		
		switch(w){
			case m_btn_start:
			SLog.i(string.Format("Starting animations : %1",selection), "PPEMenu",0);
			PluginPPEffects.activateModifier(m_registeredAnimations[selectedRow]);
			break;
			
			case m_btn_stop:
			SLog.i(string.Format("Stopping animations : %1",selection), "PPEMenu",0);
			PluginPPEffects.deactivateModifier(m_registeredAnimations[selectedRow]);
			break;
			
			case m_btn_pause:
			SLog.i(string.Format("Pausing animations : %1",selection), "PPEMenu",0);
			m_registeredAnimations[selectedRow].pause();
			break;
			
			case m_btn_resume:
			SLog.i(string.Format("Resuming animations : %1",selection), "PPEMenu",0);
			m_registeredAnimations[selectedRow].resume();
			break;
			
			case m_btn_deactivateAll:
			SLog.i("Deactivating all animationss : %1", "PPEMenu",0);
			PluginPPEffects.deactivateAllModifiers();
			break;
			
		}
		return true;
	}
	
}