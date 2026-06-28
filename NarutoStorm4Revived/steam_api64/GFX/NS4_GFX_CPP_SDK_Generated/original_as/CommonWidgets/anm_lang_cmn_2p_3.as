package duel_act_fla
{
   import flash.display.MovieClip;
   import script.duel_act_lang.smb_lang_long_r;
   import script.xcmn_btn_plat.all_btn_plat;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public dynamic class anm_lang_cmn_2p_3 extends MovieClip
   {
      
      public var all_btn_plat2:all_btn_plat;
      
      public var mc_cmd:smb_lang_long_r;
      
      public var all_btn_plat3:all_btn_plat;
      
      public var all_btn_plat1:all_btn_plat;
      
      public var all_btn_plat4:all_btn_plat;
      
      public function anm_lang_cmn_2p_3()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
      
      internal function frame3() : *
      {
         stop();
      }
      
      internal function frame4() : *
      {
         stop();
      }
   }
}

