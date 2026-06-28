package script.freebtl_cutin
{
   import flash.display.MovieClip;
   import script.freebtl_namebar.nut_namebar01;
   import script.icon_vs_l.nut_vs_l;
   import script.msg_match_m.all_nut;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol62")]
   public dynamic class nut_cutin_base00 extends MovieClip
   {
      
      public var mc_eff:MovieClip;
      
      public var mc_player_1:nut_namebar01;
      
      public var mc_knai:nut_kunai00;
      
      public var mc_player_2:nut_namebar01;
      
      public var mc_msg_match:script.msg_match_m.all_nut;
      
      public var mc_vs:nut_vs_l;
      
      public var mc_base:MovieClip;
      
      public var mc_line:MovieClip;
      
      public function nut_cutin_base00()
      {
         super();
         addFrameScript(42,this.frame43,54,this.frame55);
      }
      
      internal function frame43() : *
      {
         stop();
      }
      
      internal function frame55() : *
      {
         this.stop();
      }
   }
}

