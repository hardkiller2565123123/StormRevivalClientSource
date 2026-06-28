package duel_boss_sf_fla
{
   import flash.display.MovieClip;
   import script.duel_boss_sf.anm_sf;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public dynamic class anm_sf_in_3 extends MovieClip
   {
      
      public var mc_l:anm_sf;
      
      public function anm_sf_in_3()
      {
         super();
         addFrameScript(10,this.frame11,50,this.frame51,59,this.frame60);
      }
      
      internal function frame11() : *
      {
         this.stop();
      }
      
      internal function frame51() : *
      {
         gotoAndPlay("sf_ok");
      }
      
      internal function frame60() : *
      {
         this.stop();
      }
   }
}

