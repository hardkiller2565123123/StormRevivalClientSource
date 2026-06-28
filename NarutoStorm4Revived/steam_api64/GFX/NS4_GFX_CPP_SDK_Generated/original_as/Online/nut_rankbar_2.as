package script.net_rank
{
   import flash.display.MovieClip;
   import script.xcmn_btn_plat.all_btn_plat;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class nut_rankbar extends MovieClip
   {
      
      public var all_btn_plat_l:all_btn_plat;
      
      public var all_btn_plat_r:all_btn_plat;
      
      public var all_scb_bg:nut_scb_bg;
      
      public var mc_head:MovieClip;
      
      public var mc_rank_head:MovieClip;
      
      public var mc_rankbar00:MovieClip;
      
      public var mc_rankbar01:MovieClip;
      
      public var mc_rankbar02:MovieClip;
      
      public var mc_rankbar03:MovieClip;
      
      public var mc_rankbar04:MovieClip;
      
      public var mc_rankbar05:MovieClip;
      
      public var mc_rankbar06:MovieClip;
      
      public var mc_rankbar07:MovieClip;
      
      public var mc_rankbar08:MovieClip;
      
      public var mc_rankbar09:MovieClip;
      
      public function nut_rankbar()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
   }
}

