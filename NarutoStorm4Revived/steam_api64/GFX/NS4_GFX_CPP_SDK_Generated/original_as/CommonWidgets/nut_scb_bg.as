package script.xcmn_unset
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   public class nut_scb_bg extends MovieClip
   {
      
      private const BAR_HEIGHT_MIN:Number = 30;
      
      private var mc_scb_bar:nut_scb_bar;
      
      private var all_num:int = 0;
      
      private var view_num:int = 0;
      
      private var isHide:Boolean = true;
      
      private var bar_length:Number = 0;
      
      private var move_offset:Number = 0;
      
      private var hosei:Number = 0;
      
      public function nut_scb_bg()
      {
         super();
         this.mc_scb_bar = new nut_scb_bar();
         this.mc_scb_bar.name = "mc_bar";
         this.mc_scb_bar.x = this.x;
         this.mc_scb_bar.y = this.y;
         parent.addChild(this.mc_scb_bar);
         this.bar_length = this.height / this.scaleY - this.scale9Grid.height;
         this.bar_length = this.height - this.bar_length;
         trace("scrollbar length = " + this.bar_length);
         trace("scrollbar_pos = " + this.y);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function SetRange(param1:int, param2:int, param3:Boolean) : *
      {
         this.all_num = param1;
         this.view_num = param2;
         this.isHide = param3;
         trace("all = " + this.all_num + " : view = " + this.view_num + " : scroll = " + (this.all_num - this.view_num + 1));
         if(this.all_num <= this.view_num)
         {
            if(this.isHide)
            {
               this.visible = false;
               this.mc_scb_bar.visible = false;
            }
            this.mc_scb_bar.height = this.bar_length;
         }
         else
         {
            this.mc_scb_bar.height = this.bar_length / (this.all_num - this.view_num + 1);
            if(this.mc_scb_bar.height < this.BAR_HEIGHT_MIN)
            {
               this.mc_scb_bar.height = this.BAR_HEIGHT_MIN;
            }
            this.move_offset = (this.bar_length - this.mc_scb_bar.height) / (this.all_num - this.view_num);
            trace("bar_height = " + this.mc_scb_bar.height);
         }
      }
      
      public function UpdateScroll(param1:int) : *
      {
         var _loc2_:* = this.y - this.bar_length * 0.5 + this.mc_scb_bar.height * 0.5;
         this.mc_scb_bar.y = _loc2_ + this.move_offset * param1;
         this.mc_scb_bar.x = this.x;
      }
      
      public function SetVisibleBar(param1:Boolean) : *
      {
         this.mc_scb_bar.visible = param1;
      }
      
      private function onEnterFrameCtrl(param1:Event) : void
      {
         this.mc_scb_bar.alpha = this.alpha;
      }
   }
}

