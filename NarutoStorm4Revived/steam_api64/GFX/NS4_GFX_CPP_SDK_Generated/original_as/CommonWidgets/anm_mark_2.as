package script.map_l
{
   import flash.display.MovieClip;
   import script.icon_navi.anm_navi_m;
   import script.icon_navi.anm_navi_s;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol22")]
   public dynamic class anm_mark extends MovieClip
   {
      
      public var dmy_area:nut_tex00;
      
      public var mc_mark_on:MovieClip;
      
      public var mc_mark_s:MovieClip;
      
      public var mc_memory:MovieClip;
      
      public var mc_navi_m:anm_navi_m;
      
      public var mc_navi_s:anm_navi_s;
      
      public var mc_place:MovieClip;
      
      public function anm_mark()
      {
         super();
         addFrameScript(19,this.frame20,38,this.frame39,43,this.frame44,74,this.frame75);
      }
      
      internal function frame20() : *
      {
         gotoAndPlay("on_loop");
      }
      
      internal function frame39() : *
      {
         this.stop();
      }
      
      internal function frame44() : *
      {
         stop();
      }
      
      internal function frame75() : *
      {
         gotoAndStop("off_loop");
      }
   }
}

