package freebtl_enter_fla
{
   import flash.display.MovieClip;
   import script.freebtl_namebar.nut_namebar01;
   import script.icon_confirm.nut_conf_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class anm_setbar00_4 extends MovieClip
   {
      
      public var mc_namebaｒ00:nut_namebar01;
      
      public var mc_conf_l:nut_conf_l;
      
      public function anm_setbar00_4()
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

