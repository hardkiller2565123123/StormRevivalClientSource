package script.duel_act
{
   import flash.display.MovieClip;
   import script.duel_act_lang.smb_lang_sec;
   import script.xcmn_btn_plat.all_btn_plat;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol28")]
   public dynamic class nut_sec extends MovieClip
   {
      
      public var mc_msg:smb_lang_sec;
      
      public var all_btn_plat2:all_btn_plat;
      
      public var all_btn_plat1:all_btn_plat;
      
      public function nut_sec()
      {
         super();
         addFrameScript(17,this.frame18,26,this.frame27,40,this.frame41);
      }
      
      internal function frame18() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame27() : *
      {
         stop();
      }
      
      internal function frame41() : *
      {
         stop();
      }
   }
}

