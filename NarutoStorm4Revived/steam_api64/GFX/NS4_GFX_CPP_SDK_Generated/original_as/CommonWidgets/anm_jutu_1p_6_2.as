package duel_cmn_fla
{
   import flash.display.MovieClip;
   import script.duel_cmn.nut_jutu;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol294")]
   public dynamic class anm_jutu_1p_6 extends MovieClip
   {
      
      public var mc_jutu:nut_jutu;
      
      public function anm_jutu_1p_6()
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

