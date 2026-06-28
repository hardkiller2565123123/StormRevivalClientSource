package script.map_sm
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_btn_plat.all_btn_plat;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol49")]
   public class anm_quest extends MovieClip
   {
      
      public var btn_icon:all_btn_plat;
      
      public var mc_num:MovieClip;
      
      private var m_eventNum:int = 0;
      
      private var m_txt:smb_font = null;
      
      private var m_btn:MovieClip = null;
      
      public function anm_quest()
      {
         super();
         addFrameScript(0,this.frame1,9,this.frame10,19,this.frame20);
         this.m_txt = this["mc_num"].txt_num;
         this.m_btn = this["btn_icon"];
         this.m_btn.gotoAndStop("btn_r1");
         this.m_txt.SetText(this.m_eventNum.toString());
      }
      
      public function SetEventNum(param1:int, param2:Boolean) : *
      {
         this.m_eventNum = param1;
         if(param2 == true)
         {
            gotoAndPlay("num_in");
         }
         else
         {
            gotoAndStop("loop");
            this.m_txt.visible = true;
            this.m_txt.SetText(this.m_eventNum.toString());
         }
      }
      
      public function IsCntUpAnmation() : Boolean
      {
         return currentLabel != "loop";
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame10() : *
      {
         this.m_txt.SetText(this.m_eventNum.toString());
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_JINGLE);
      }
      
      internal function frame20() : *
      {
         gotoAndStop("loop");
      }
   }
}

