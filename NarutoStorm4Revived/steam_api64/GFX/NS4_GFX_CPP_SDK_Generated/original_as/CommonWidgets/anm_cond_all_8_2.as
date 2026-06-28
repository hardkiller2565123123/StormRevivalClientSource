package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.icon_result2.nut_rslt_ng;
   import script.icon_result2.nut_rslt_ok;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol33")]
   public dynamic class anm_cond_all_8 extends MovieClip
   {
      
      public var mc_bns_1:MovieClip;
      
      public var mc_bns_2:MovieClip;
      
      public var mc_bns_3:MovieClip;
      
      public var mc_bns_4:MovieClip;
      
      public var mc_btl:MovieClip;
      
      public var mc_btl_set:MovieClip;
      
      public var mc_cond_tit:MovieClip;
      
      public var mc_ng:nut_rslt_ng;
      
      public var mc_scb:nut_scb_bg;
      
      public var mc_suc:nut_rslt_ok;
      
      public function anm_cond_all_8()
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

