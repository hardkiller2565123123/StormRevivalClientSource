package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import script.freebtl_cp_rate.all_freebtl_rate;
   import script.freebtl_cp_txt.all_nut;
   import script.icon_player_m_txt.nut_icon_player_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol73")]
   public dynamic class anm_cap00_29 extends MovieClip
   {
      
      public var all_cap_rate:all_freebtl_rate;
      
      public var all_player_m:nut_icon_player_m;
      
      public var all_cap_txt:all_nut;
      
      public function anm_cap00_29()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

