class DebugMenu extends PopupMenu{

	TextListboxWidget m_test;
	
	
	void DebugMenu(){
	}

	void ~DebugMenu(){
	}


	override void Init(){
		//m_test = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("txt_list_test"));
		
		//m_test.AddItem("Hand recoil pattern", NULL, 0);
		//m_test.AddItem("Camera recoil pattern", NULL, 0);
		//m_test.AddItem("Mouse recoil pattern", NULL, 0);
	}

	override void OnShow(){
		
	}

	override void OnHide(){
		
	}

	override bool OnClick( Widget w, int x, int y, int button ){
		return false;
	}

}