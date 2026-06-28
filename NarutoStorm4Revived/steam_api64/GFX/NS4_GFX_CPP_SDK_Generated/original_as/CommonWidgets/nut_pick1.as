package script.freebtl_leag
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class nut_pick1 extends MovieClip
   {
      
      public var mc_pick1_player_1:MovieClip;
      
      public var mc_pick1_player_2:MovieClip;
      
      public var mc_pick1_player_3:MovieClip;
      
      public var mc_pick1_player_4:MovieClip;
      
      public function nut_pick1()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

