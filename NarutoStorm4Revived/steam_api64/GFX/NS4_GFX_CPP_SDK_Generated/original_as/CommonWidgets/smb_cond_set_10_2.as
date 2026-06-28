package duel_cond_fla
{
   import adobe.utils.*;
   import flash.accessibility.*;
   import flash.desktop.*;
   import flash.display.*;
   import flash.errors.*;
   import flash.events.*;
   import flash.external.*;
   import flash.filters.*;
   import flash.geom.*;
   import flash.globalization.*;
   import flash.media.*;
   import flash.net.*;
   import flash.net.drm.*;
   import flash.printing.*;
   import flash.profiler.*;
   import flash.sampler.*;
   import flash.sensors.*;
   import flash.system.*;
   import flash.text.*;
   import flash.text.engine.*;
   import flash.text.ime.*;
   import flash.ui.*;
   import flash.utils.*;
   import flash.xml.*;
   import script.icon_checkbox.nut_checkbox;
   import script.icon_new.nut_new;
   import script.xcmn_menu.nut_line;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol30")]
   public dynamic class smb_cond_set_10 extends MovieClip
   {
      
      public var all_checkbox:nut_checkbox;
      
      public var all_line:nut_line;
      
      public var dmy_item:nut_tex00;
      
      public var mc_bns_cond:MovieClip;
      
      public var mc_item:MovieClip;
      
      public var mc_new:nut_new;
      
      public var mc_num:MovieClip;
      
      public function smb_cond_set_10()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         if(this.mc_item.txt_item.IsArabic() == true)
         {
            if(this.mc_new.x < 0)
            {
               this.mc_new.x *= -1;
               this.mc_new.scaleX = -1;
               this.mc_bns_cond.x *= -1;
               this.mc_item.x *= -1;
               this.mc_num.x *= -1;
               this.dmy_item.x *= -1;
               this.all_checkbox.x *= -1;
            }
         }
      }
   }
}

