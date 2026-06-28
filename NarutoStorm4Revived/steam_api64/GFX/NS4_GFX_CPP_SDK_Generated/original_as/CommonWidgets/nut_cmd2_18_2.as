package duel_boss_fla
{
   import flash.display.MovieClip;
   import script.d_boss_plat.nut_btn;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol48")]
   public dynamic class nut_cmd2_18 extends MovieClip
   {
      
      public var mc_btn:nut_btn;
      
      public function nut_cmd2_18()
      {
         super();
         addFrameScript(16,this.frame17,38,this.frame39,42,this.frame43);
      }
      
      internal function frame17() : *
      {
         this.stop();
      }
      
      internal function frame39() : *
      {
         this.stop();
         this.parent.visible = false;
      }
      
      internal function frame43() : *
      {
         this.stop();
      }
   }
}

