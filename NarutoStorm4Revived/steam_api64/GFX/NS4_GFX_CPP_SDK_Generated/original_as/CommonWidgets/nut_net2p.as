package script.gauge_net
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_net.nut_icon_wave;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public class nut_net2p extends MovieClip
   {
      
      public var mc_wav:nut_icon_wave;
      
      public var txt_id:smb_font;
      
      public function nut_net2p()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      public function Initialize(param1:String, param2:int) : *
      {
         var _loc3_:smb_font = null;
         var _loc4_:MovieClip = null;
         if(param1 != "")
         {
            this.visible = true;
            _loc3_ = smb_font(this["txt_id"]);
            if(_loc3_)
            {
               _loc3_.SetText(param1);
            }
            _loc4_ = MovieClip(this["mc_wav"]);
            if(_loc4_)
            {
               if(param2 == 0)
               {
                  _loc4_.visible = false;
               }
               else
               {
                  _loc4_.visible = true;
                  _loc4_.gotoAndStop(param2);
               }
            }
         }
         else
         {
            this.visible = false;
         }
      }
      
      internal function frame1() : *
      {
         this.txt_id.SetTextSize(28);
         this.txt_id.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
   }
}

